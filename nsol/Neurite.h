/**
 * @file    Neurite.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_NEURITE__
#define __NSOL_NEURITE__

#include <nsol/api.h>
#include "NsolTypes.h"
#include "Section.h"

#include <stack>

#include <iostream>


namespace nsol {

  class Dendrite;
  class Axon;
  class NeuriteStats;

  class Neurite
  {

    template< class NODE,
              class SECTION,
              class DENDRITE,
              class AXON,
              class SOMA,
              class NEURONMORPHOLOGY,
              class NEURON > friend class SwcReaderTemplated;
    friend class BBPSDKreader;

  public:

    //! Possible types of neurite
    typedef enum
    {
      UNDEFINED = 0,
      DENDRITE,
      AXON
    } TNeuriteType;

    friend std::ostream & operator<< ( std::ostream & os,
                                       const TNeuriteType & rhs)
    {
      switch ( rhs )
      {
      case DENDRITE:
        return os << "DENDRITE";
        break;
      case AXON:
        return os << "AXON";
        break;
      default:
        return os << "UNDEFINED";
      }
      return os;
    }

    //! Default constructor
    NSOL_API
    Neurite( TNeuriteType neuriteType = DENDRITE );

    NSOL_API
    virtual ~Neurite();

    //! Get the type of neurite
    NSOL_API
    TNeuriteType & neuriteType( void );

    NSOL_API
    NeuronMorphologyPtr morphology( void ) const;

    NSOL_API
    NeuronMorphologyPtr morphology( NeuronMorphologyPtr morphology );

    NSOL_API
    bool hasMorphology( void ) const;

    NSOL_API
    SectionPtr firstSection( void ) const ;

    NSOL_API
    virtual void firstSection( SectionPtr section );

    NSOL_API
    Sections sections( void ) const;

    //TODO: this methods should disappear
    NSOL_API
    void computeBranchBifurcations( void );

    NSOL_API
    unsigned int numBranches( void );

    NSOL_API
    unsigned int numBifurcations( void );

    /**
     * Returns object as NeuriteStats
     * @return pointer to NeuriteStats object
     */
    NSOL_API
    virtual NeuriteStats * stats( void );

    NSOL_API
    virtual NeuritePtr clone( void ) const;

    NSOL_API
    bool operator == ( Neurite & other );

    NSOL_API
    bool operator != ( Neurite & other );

  protected:

    NSOL_API
    void _addBifurcationCount( unsigned int numBifurcations );

    NSOL_API
    void _addBranchCount( unsigned int numBranches );

    TNeuriteType _neuriteType;

    SectionPtr _firstSection;

    NeuronMorphologyPtr _morphology;

    unsigned int _numBranches;

    unsigned int _numBifurcations;
  };

}

#endif
