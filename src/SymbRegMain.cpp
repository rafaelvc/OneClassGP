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
 *  \file   SymbRegMain.cpp
 *  \brief  Implementation of the main routine for the symbolic regression problem.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.10.2.1 $
 *  $Date: 2007/05/09 01:51:24 $
 */

#include "beagle/GP.hpp"
#include "SymbRegEvalOp.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <fstream> 
#include <vector> 
#include <string>
#include <string.h>

using namespace std;
using namespace Beagle;

/*!
 *  \brief Main routine for the function symbolic regression problem.
 *  \param argc Number of arguments on the command-line.
 *  \param argv Arguments on the command-line.
 *  \return Return value of the program.
 *  \ingroup SymbReg
 */

double get_atr_value_(fstream & f) 
{
    std::string str;
    char c = f.get();
    while (c && c != ',' && c != '\n' && !f.eof()) {
 	str.push_back(c);	
        c = f.get();
    }
    return atof ( str.c_str() );
}

int main(int argc, char *argv[]) {

  try {
    // 1: Build primitives.
    GP::PrimitiveSet::Handle lSet = new GP::PrimitiveSet;

    lSet->insert(new GP::Add);
    lSet->insert(new GP::Subtract);
    lSet->insert(new GP::Multiply);
    lSet->insert(new GP::Divide);

    // lSet->insert(new GP::Sin);
    // lSet->insert(new GP::Cos);
    // lSet->insert(new GP::Log);
    // lSet->insert(new GP::EphemeralDouble);
    //lSet->insert(new GP::TokenT<Double>("Pi", Double(M_PI)));

    lSet->insert(new GP::TokenT<Double>("F1"));
    lSet->insert(new GP::TokenT<Double>("F2"));
    lSet->insert(new GP::TokenT<Double>("F3"));
    lSet->insert(new GP::TokenT<Double>("F4"));
    lSet->insert(new GP::TokenT<Double>("F5"));
    lSet->insert(new GP::TokenT<Double>("F6"));
    lSet->insert(new GP::TokenT<Double>("F7"));
    lSet->insert(new GP::TokenT<Double>("F8"));
    lSet->insert(new GP::TokenT<Double>("F9"));
    lSet->insert(new GP::TokenT<Double>("F10"));

    lSet->insert(new GP::TokenT<Double>("F11"));
    lSet->insert(new GP::TokenT<Double>("F12"));
    lSet->insert(new GP::TokenT<Double>("F13"));
    lSet->insert(new GP::TokenT<Double>("F14"));
    lSet->insert(new GP::TokenT<Double>("F15"));
    lSet->insert(new GP::TokenT<Double>("F16"));
    lSet->insert(new GP::TokenT<Double>("F17"));
    lSet->insert(new GP::TokenT<Double>("F18"));
    lSet->insert(new GP::TokenT<Double>("F19"));
    lSet->insert(new GP::TokenT<Double>("F20"));

    lSet->insert(new GP::TokenT<Double>("F21"));
    lSet->insert(new GP::TokenT<Double>("F22"));
    lSet->insert(new GP::TokenT<Double>("F23"));
    lSet->insert(new GP::TokenT<Double>("F24"));
    lSet->insert(new GP::TokenT<Double>("F25"));
    lSet->insert(new GP::TokenT<Double>("F26"));
    lSet->insert(new GP::TokenT<Double>("F27"));
    lSet->insert(new GP::TokenT<Double>("F28"));
    lSet->insert(new GP::TokenT<Double>("F29"));
    lSet->insert(new GP::TokenT<Double>("F30"));

    // lSet->insert(new GP::EphemeralDouble);
    //lSet->insert(new GP::TokenT<Double>("Pi", Double(M_PI)));
    // 2: Build a system.
    GP::System::Handle lSystem = new GP::System(lSet);
    // 3: Build evaluation operator.
    SymbRegEvalOp::Handle lEvalOp = new SymbRegEvalOp;
    // 4: Build an evolver and a vivarium.
    GP::Evolver::Handle lEvolver = new GP::Evolver(lEvalOp);
    GP::Vivarium::Handle lVivarium = new GP::Vivarium;
    // 5: Initialize and evolve the vivarium.
    lEvolver->initialize(lSystem, argc, argv);
    lEvolver->evolve(lVivarium);
 
  // Test Phase 
  std::vector<Sample *> test_set;
  lEvalOp->get_test_set(test_set);

  fstream f;
  f.open("breast/wdbc_B.data.teste5");

  while(!f.eof()){

	Sample * s = new Sample();
	s->type = new std::string();      
	s->type->push_back(f.get()); // label values
	f.get(); //, 

	// attribute values
 	s->f1 = get_atr_value_(f); 
 	s->f2 = get_atr_value_(f); 
 	s->f3 = get_atr_value_(f); 
 	s->f4 = get_atr_value_(f); 
 	s->f5 = get_atr_value_(f); 
 	s->f6 = get_atr_value_(f); 
 	s->f7 = get_atr_value_(f); 
 	s->f8 = get_atr_value_(f); 
 	s->f9 = get_atr_value_(f); 

 	s->f10 = get_atr_value_(f); 
 	s->f11 = get_atr_value_(f); 
 	s->f12 = get_atr_value_(f); 
 	s->f13 = get_atr_value_(f); 
 	s->f14 = get_atr_value_(f); 
 	s->f15 = get_atr_value_(f); 
 	s->f16 = get_atr_value_(f); 
 	s->f17 = get_atr_value_(f); 
 	s->f18 = get_atr_value_(f); 
 	s->f19 = get_atr_value_(f); 

 	s->f20= get_atr_value_(f); 
 	s->f21= get_atr_value_(f); 
 	s->f22= get_atr_value_(f); 
 	s->f23= get_atr_value_(f); 
 	s->f24= get_atr_value_(f); 
 	s->f25= get_atr_value_(f); 
 	s->f26= get_atr_value_(f); 
 	s->f27= get_atr_value_(f); 
 	s->f28= get_atr_value_(f); 
 	s->f29= get_atr_value_(f); 
 	s->f30 = get_atr_value_(f); 

	test_set.push_back(s);
   }
   f.close();

  int size_set_test = test_set.size(); 
  Sample * s;
  // GP::Context::Handle lCtxTest = new GP::Context::Alloc;
  GP::Context::Alloc::Handle lContextAlloc =  castHandleT<GP::Context::Alloc>(lSystem->getContextAllocatorHandle());
  GP::Context::Handle lCtxTest = castHandleT<GP::Context>(lContextAlloc->allocate());

  lCtxTest->setSystemHandle(lSystem);  // way we say how the individual is configurated (operators) ??

  GP::Deme::Handle & deme = (*lVivarium)[0]; // Working with just one deme

  /// Gets the fitness average of last population over the test set 
  //  double avg_rate = 0.0;
  double max_better_hits = 0.0;
  unsigned int better_indv;

  vector<double> gp_out(size_set_test,0.0), gp_out_(size_set_test,0.0);		
  vector<int> class_samples(size_set_test,0), class_samples_(size_set_test,0);
  double tp_,fp_,tn_,fn_; 

  for (unsigned int i = 0; i < deme->size(); i++) { 
	GP::Individual::Handle & indv  =  (*deme)[i];
	lCtxTest->setIndividualHandle(indv);
  	double hits = 0.0;
	double tp = 0.0, tn = 0.0, fp = 0.0, fn = 0.0;
	for(unsigned int j=0; j < size_set_test; j++)
	{
    		s = test_set[j];
		lEvalOp->setValue("F1", s->f1, *lCtxTest);
		lEvalOp->setValue("F2", s->f2, *lCtxTest);
		lEvalOp->setValue("F3", s->f3, *lCtxTest);
		lEvalOp->setValue("F4", s->f4, *lCtxTest); 
		lEvalOp->setValue("F5", s->f5, *lCtxTest);
		lEvalOp->setValue("F6", s->f6, *lCtxTest);
		lEvalOp->setValue("F7", s->f7, *lCtxTest);
		lEvalOp->setValue("F8", s->f8, *lCtxTest); 
		lEvalOp->setValue("F9", s->f9, *lCtxTest);

		lEvalOp->setValue("F10", s->f10, *lCtxTest);
		lEvalOp->setValue("F11", s->f11, *lCtxTest);
		lEvalOp->setValue("F12", s->f12, *lCtxTest); 
		lEvalOp->setValue("F13", s->f13, *lCtxTest);
		lEvalOp->setValue("F14", s->f14, *lCtxTest);
		lEvalOp->setValue("F15", s->f15, *lCtxTest);
		lEvalOp->setValue("F16", s->f16, *lCtxTest); 
		lEvalOp->setValue("F17", s->f17, *lCtxTest);
		lEvalOp->setValue("F18", s->f18, *lCtxTest); 
		lEvalOp->setValue("F19", s->f19, *lCtxTest);

		lEvalOp->setValue("F20", s->f20, *lCtxTest);
		lEvalOp->setValue("F21", s->f21, *lCtxTest);
		lEvalOp->setValue("F22", s->f22, *lCtxTest);
		lEvalOp->setValue("F23", s->f23, *lCtxTest);
		lEvalOp->setValue("F24", s->f24, *lCtxTest); 
		lEvalOp->setValue("F25", s->f25, *lCtxTest);
		lEvalOp->setValue("F26", s->f26, *lCtxTest);
		lEvalOp->setValue("F27", s->f27, *lCtxTest);
		lEvalOp->setValue("F28", s->f28, *lCtxTest); 
		lEvalOp->setValue("F29", s->f29, *lCtxTest);
		lEvalOp->setValue("F30", s->f30, *lCtxTest);

		Double lResult = 0.0;
		indv->run(lResult, *lCtxTest); 

 		if ((lResult >= 0.0 && ISCLASS1((s->type)->c_str())) ||
		    (lResult  < 0.0 && ISCLASS2((s->type)->c_str())))
	    	{
		    hits+=1.0;
	    	}

		if (lResult >= 0.0 && ISCLASS1((s->type)->c_str())) {
			tp += 1;
		}
		else if (lResult < 0.0 && ISCLASS2((s->type)->c_str()))  {
			tn += 1;
		}
		else if (lResult >= 0.0 && ISCLASS2((s->type)->c_str())) {
			fp += 1;
		}
		else if (lResult  < 0.0 && ISCLASS1((s->type)->c_str()))  {
			fn += 1;
		}

		gp_out[j] = lResult;
		if (ISCLASS1((s->type)->c_str()))
			class_samples[j] = 1;
		else
			class_samples[j] = 0;

	}

	if (hits > max_better_hits) {
		max_better_hits=hits;
		better_indv = i + 1;
		tp_ = tp;
		tn_ = tn;
		fp_ = fp;
		fn_ = fn;
		gp_out_ = gp_out;
		class_samples_ = class_samples;
	} 
  }

  double best_rate = max_better_hits / (1.0 * size_set_test);  
  int targets = count(  class_samples_.begin(), class_samples_.end(), 1 );
  int outliers = count(  class_samples_.begin(), class_samples_.end(), 0 );

  cout.flush();

   const char * f_fold  = "result_fold.txt";
   fstream ff;
   ff.open(f_fold, fstream::out);
//   ff << "TEST PHASE: \nDetection rate of best individual in the last population: " <<  best_rate << endl;
   ff << "Rate best individual: " <<  best_rate << endl;
   ff << "Individual number: " << better_indv << endl;
   ff << "Numer of hits: " << max_better_hits << endl;
   ff << "DB test size: " << size_set_test << endl;
   ff << "TP: " << tp_ << endl;
   ff << "FP: " << fp_ << endl;
   ff << "TN: " << tn_ << endl;
   ff << "FN: " << fn_ << endl;
   ff << "Accuracy: " <<  ((tn_ + tp_) / (1.0 * size_set_test)) << endl;
   ff << "TP/P: " << (tp_/(1.0*targets)) << endl;
   ff << "TN/N: " << (tn_/(1.0*outliers)) << endl;
   ff << "Targets: " << targets << endl;
   ff << "Outliers: " << outliers << endl;
   ff << "GPOUT: ";
   for (int i = 0; i < size_set_test; i++) { 
   	ff << gp_out_[i];
	if ((i+1) < size_set_test)
		ff << ",";
   }
   ff << endl;
   ff << "CLASS: ";
   for (int i = 0; i < size_set_test; i++) { 
   	ff << class_samples_[i];
	if ((i+1) < size_set_test)
		ff << ",";
   }
   ff << endl;
   ff.close();

  }
  catch(Exception& inException) {
    inException.terminate();
  }
  catch(exception& inException) {
    cerr << "Standard exception catched:" << endl;
    cerr << inException.what() << endl << flush;
    return 1;
  }
  catch(...) {
    cerr << "Unknown exception catched!" << endl << flush;
    return 1;
  }

   return 0;
}

