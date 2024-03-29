/*
 *  Open BEAGLE
 *  Copyright (C) 2001-2007 by Christian Gagne and Marc Parizeau
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact:
 *  Laboratoire de Vision et Systemes Numeriques
 *  Departement de genie electrique et de genie informatique
 *  Universite Laval, Quebec, Canada, G1K 7P4
 *  http://vision.gel.ulaval.ca
 *
 */

/*!
 *  \file   SymbRegEvalOp.cpp
 *  \brief  Implementation of the class SymbRegEvalOp.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.9.2.1 $
 *  $Date: 2007/05/09 01:51:24 $
 */

#include "beagle/GP.hpp"
#include "SymbRegEvalOp.hpp"

#include <cmath>
#include <string.h>
#include <fstream>

using namespace Beagle;
using namespace std;

/*!
 *  \brief Construct a new symbolic regression evaluation operator.
 */
SymbRegEvalOp::SymbRegEvalOp() :
  GP::EvaluationOp("SymbRegEvalOp"), 
 db_samples(),
 db_samples_training(), 
 db_samples_test()
/*  mX(0),
  mY(0)*/
{ }


/*!
 *  \brief Evaluate the individual fitness for the symbolic regression problem.
 *  \param inIndividual Individual to evaluate.
 *  \param ioContext Evolutionary context.
 *  \return Handle to the fitness measure,
 */
Fitness::Handle SymbRegEvalOp::evaluate(GP::Individual& inIndividual, GP::Context& ioContext)
{ 
  // double lSquareError = 0.0;
  double hits = 0.0;
  Sample * s;
  int size_training_set = db_samples_training.size(); 
  double tp = tn = 0.0;
  vector<int> class_samples(size_training_set,0);
  for(unsigned int i=0; i < size_training_set; i++) 
  {
    s = db_samples_training[i];

    setValue("F1", s->f1, ioContext);
    setValue("F2", s->f2, ioContext);
    setValue("F3", s->f3, ioContext);
    setValue("F4", s->f4, ioContext);
    setValue("F5", s->f5, ioContext);
    setValue("F6", s->f6, ioContext);
    setValue("F7", s->f7, ioContext);
    setValue("F8", s->f8, ioContext);
    setValue("F9", s->f9, ioContext);

    setValue("F10", s->f10, ioContext);
    setValue("F11", s->f11, ioContext);
    setValue("F12", s->f12, ioContext);
    setValue("F13", s->f13, ioContext);
    setValue("F14", s->f14, ioContext);
    setValue("F15", s->f15, ioContext);
    setValue("F16", s->f16, ioContext);
    setValue("F17", s->f17, ioContext);
    setValue("F18", s->f18, ioContext);
    setValue("F19", s->f19, ioContext);
    
    setValue("F20", s->f20, ioContext);
    setValue("F21", s->f21, ioContext);
    setValue("F22", s->f22, ioContext);
    setValue("F23", s->f23, ioContext);
    setValue("F24", s->f24, ioContext);
    setValue("F25", s->f25, ioContext);
    setValue("F26", s->f26, ioContext);
    setValue("F27", s->f27, ioContext);
    setValue("F28", s->f28, ioContext);
    setValue("F29", s->f29, ioContext);
    setValue("F30", s->f30, ioContext);

    Double lResult = 0.0 ;
    inIndividual.run(lResult, ioContext);

 /*   if ((lResult >= 0.0 && ISCLASS1((s->type)->c_str())) ||
	(lResult  < 0.0 && ISCLASS2((s->type)->c_str()))) 
    {
	    hits+=1.0;
    } */

    if (lResult >= 0.0 && ISCLASS1((s->type)->c_str())) {
	tp += 1.0;
    }
    else if (lResult < 0.0 && ISCLASS2((s->type)->c_str()))  {
	tn += 1.0;
    }

    if (ISCLASS1((s->type)->c_str()))
 	class_samples[i] = 1;
    else
	class_samples[i] = 0;

  }
  int targets = count(  class_samples.begin(), class_samples.end(), 1 );
  int outliers = size_training_set - targets;
  double lFitness = ( pow ((tp/(targets*1.0)),2) + pow((tn/(outliers*1.0)),2) ) / 2.0; 
  return new FitnessSimple(lFitness);
}


double get_atr_value(fstream & f) 
{
    std::string str;
    char c = f.get();
    while (c && c != ',' && c != '\n' && !f.eof()) {
 	str.push_back(c);	
        c = f.get();
    }
    return atof ( str.c_str() );
}

void SymbRegEvalOp::postInit(System& ioSystem)
{
   GP::EvaluationOp::postInit(ioSystem);
  
   fstream f;
   f.open("breast/wdbc_B.data.treino5");
   while(!f.eof()){
       
	Sample * s = new Sample();	
	s->type = new std::string();      
	s->type->push_back(f.get()); // label values
	f.get(); //,
	// attribute values

 	s->f1 = get_atr_value(f); 
 	s->f2 = get_atr_value(f); 
 	s->f3 = get_atr_value(f); 
 	s->f4 = get_atr_value(f); 
 	s->f5 = get_atr_value(f); 
 	s->f6 = get_atr_value(f); 
 	s->f7 = get_atr_value(f); 
 	s->f8 = get_atr_value(f); 
 	s->f9 = get_atr_value(f); 

 	s->f10 = get_atr_value(f); 
 	s->f11 = get_atr_value(f); 
 	s->f12 = get_atr_value(f); 
 	s->f13 = get_atr_value(f); 
 	s->f14 = get_atr_value(f); 
 	s->f15 = get_atr_value(f); 
 	s->f16 = get_atr_value(f); 
 	s->f17 = get_atr_value(f); 
 	s->f18 = get_atr_value(f); 
 	s->f19 = get_atr_value(f); 

 	s->f20 = get_atr_value(f); 
 	s->f21 = get_atr_value(f); 
 	s->f22 = get_atr_value(f); 
 	s->f23 = get_atr_value(f); 
 	s->f24 = get_atr_value(f); 
 	s->f25 = get_atr_value(f); 
 	s->f26 = get_atr_value(f); 
 	s->f27 = get_atr_value(f); 
 	s->f28 = get_atr_value(f); 
 	s->f29 = get_atr_value(f); 
 	s->f30 = get_atr_value(f); 
	
	db_samples_training.push_back(s);
   }
   f.close();
   
}
