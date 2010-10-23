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
 *  \file   SymbRegEvalOp.hpp
 *  \brief  Definition of the type SymbRegEvalOp.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.8.2.1 $
 *  $Date: 2007/05/09 01:51:24 $
 */

/*!
 *  \defgroup SymbReg Symbolic Regression Example
 *  \brief Symbolic regression (symbreg): A simple GP example with Open BEAGLE.
 *
 *  \par Objective
 *  Find a function of one independent variable and one dependent variable, in
 *  symbolic form, that fits a given sample of 20 \f$(x_i,y_i)\f$ data points,
 *  where the target function is the quadratic polynomial \f$x^4 + x^3 + x^2 + x\f$.
 *
 *  \par Terminal set
 *  - X (the independent variable)
 *  - PI
 *  - Ephemeral constants randomly generated in [-1,1]
 *
 *  \par Function set
 *  - +
 *  - -
 *  - *
 *  - /     (protected division)
 *  - SIN
 *  - COS
 *  - EXP
 *  - LOG   (protected logarithm)
 *
 *  \par Fitness cases
 *  The given sample of 20 data points \f$(x_i,y_i)\f$, randomly chosen within
 *  interval [-1,1].
 *
 *  \par Fitness
 *  \f$\frac{1.}{1.+RMSE}\f$ where RMSE is the Root Mean Square Error on the
 *  fitness cases.
 *
 *  \par Stopping criteria
 *  When the evolution reaches the maximum number of generations.
 *
 *  \par Reference
 *  John R. Koza, "Genetic Programming: On the Programming of Computers by Means
 *  of Natural Selection", MIT Press, 1992, pages 162-169.
 *
 */
 
#ifndef SymbRegEvalOp_hpp
#define SymbRegEvalOp_hpp

#include "beagle/GP.hpp"
#include <string>
#include <vector>

/* #define CLASS1 "Iris-setosa"
#define CLASS2 "Iris-versicolor"
#define CLASS3 "Iris-virginica"*/

#define CLASS1 "B"
#define CLASS2 "O"
#define DB_FILE "breast/wdbc_B.data"

#define ISCLASS1(c) !strncmp(CLASS1,c,1)
#define ISCLASS2(c) !strncmp(CLASS2,c,1) 
// #define ISCLASS3(c) !strncmp(CLASS1,c,14)

struct Sample {
        public:
                Sample() {};
                ~Sample() {}
                void clearData() {if (type) delete type;} //a way to explicity prevent memory leaks 
                Beagle::Double f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,
			       f11,f12,f13,f14,f15,f16,f17,f18,f19,f20,
			       f21,f22,f23,f24,f25,f26,f27,f28,f29,f30;
                std::string * type;
};

/*!
 *  \class SymbRegEvalOp SymbRegEvalOp.hpp "SymbRegEvalOp.hpp"
 *  \brief The individual evaluation class operator for the problem of symbolic regression.
 *  \ingroup SymbReg
 */
class SymbRegEvalOp : public Beagle::GP::EvaluationOp {

public:

  //! SymbRegEvalOp allocator type.
  typedef Beagle::AllocatorT<SymbRegEvalOp,Beagle::GP::EvaluationOp::Alloc>
          Alloc;
  //!< SymbRegEvalOp handle type.
  typedef Beagle::PointerT<SymbRegEvalOp,Beagle::GP::EvaluationOp::Handle>
          Handle;
  //!< SymbRegEvalOp bag type.
  typedef Beagle::ContainerT<SymbRegEvalOp,Beagle::GP::EvaluationOp::Bag>
          Bag;

  explicit SymbRegEvalOp();

  virtual Beagle::Fitness::Handle evaluate(Beagle::GP::Individual& inIndividual,
                                           Beagle::GP::Context& ioContext);
  virtual void postInit(Beagle::System& ioSystem);

  void get_test_set(std::vector<Sample *> & vet) {vet = db_samples_test;};

protected:
	std::vector<Sample *> db_samples;
	std::vector<Sample *> db_samples_training;
	std::vector<Sample *> db_samples_test;


/*  std::vector<Beagle::Double> mX;
  std::vector<Beagle::Double> mY; */

};

#endif // SymbRegEvalOp_hpp
