/**
 * @file    NeuronMorphologyCachedStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_NEURON_MORPHOLOGY_CACHED_STATS__
#define __NSOL_NEURON_MORPHOLOGY_CACHED_STATS__

#include <nsol/api.h>

#include "Cached.h"
#include "NeuronMorphologyStats.h"

namespace nsol
{

  /** \class NeuronMorphologyCachedStats
   *  \brief This class allows to cache the stats for neuronmorphologys
   *
   *  Using this class instead of NeuronMorphology or NeuronMorphologyStats
   *  when constructing the hierarchy allows to call the method stats from
   *  base NeuronMorphology class and get the corresponding volume, surface
   *  and length. If the cached value is dirty then the actual computation
   *  process is done. In case is clean the cached value is returned
   *  directly.
   *
   *  Example: @include examples/neuronStats.cpp
   */
  class NeuronMorphologyCachedStats
    : public virtual NeuronMorphologyStats
    , public Cached<>
  {


  public:

    // //! Stats that can be cached for NeuronMorphologyStats
    // typedef enum
    // {
    //   DENDRITIC_VOLUME = 0,
    //   AXON_VOLUME,
    //   NEURITIC_VOLUME,
    //   VOLUME,
    //   DENDRITIC_SURFACE,
    //   AXON_SURFACE,
    //   NEURITIC_SURFACE,
    //   SURFACE,
    //   DENDRITIC_LENGTH,
    //   AXON_LENGTH,
    //   NEURITIC_LENGTH,
    //   DENDRITIC_BIFURCATIONS,
    //   AXON_BIFURCATIONS,
    //   NEURITIC_BIFURCATIONS,
    //   NEURON_MORPHOLOGY_NUM_CACHED_VALUES
    // } TNeuronMorphologyCachedValues;


    /**
     * Default constructor
     */
    NSOL_API
    NeuronMorphologyCachedStats( void )
      : NeuronMorphologyStats( )
    {
    }


    NSOL_API
    NeuronMorphologyCachedStats( SomaPtr soma_ )
      : NeuronMorphologyStats( soma_ )
    {
    }

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~NeuronMorphologyCachedStats( void ) {}

    NSOL_API
    virtual float getStat( TNeuronMorphologyStat stat,
                           TAggregation agg = /*TAggregation::*/TOTAL ) const;

    /**
     * Set dirty a cached stat and propagates dirty to
     * parent neuronmorphology
     * @param id identifier of the property to set dirty. It also propagates
     * dirty state to parent neuronmorphology. id value has to be one from
     * TNeuronMorphologyCachedValues (checked only on debug compiling).
     */
    NSOL_API
    virtual void setAndPropagateDirty( unsigned int id );

    /**
     * Set dirty all cached stats and propagates dirty to parent
     * neuron morphology
     */
    NSOL_API
    virtual void setAndPropagateDirty( void );


    // NSOL_API
    // virtual float dendriticVolume( void ) const;

    // NSOL_API
    // virtual float axonVolume( void ) const;

    // NSOL_API
    // virtual float neuriticVolume( void ) const;

    // NSOL_API
    // virtual float somaVolume( void ) const;

    // NSOL_API
    // virtual float volume( void ) const;

    // NSOL_API
    // virtual float dendriticSurface( void ) const;

    // NSOL_API
    // virtual float axonSurface( void ) const;

    // NSOL_API
    // virtual float neuriticSurface( void ) const;

    // // NSOL_API
    // // virtual float somaSurface( void ) const;

    // NSOL_API
    // virtual float surface( void ) const;

    // NSOL_API
    // virtual float dendriticLength( void ) const;

    // NSOL_API
    // virtual float axonLength( void ) const;

    // NSOL_API
    // virtual float neuriticLength( void ) const;

    // NSOL_API
    // virtual unsigned int dendriticBifurcations( void ) const;

    // NSOL_API
    // virtual unsigned int axonBifurcations( void ) const;

    // NSOL_API
    // virtual unsigned int neuriticBifurcations( void ) const;


  }; // class NeuronMorphologyCachedStats

} // namespace nsol

#endif // __NSOL_NEURON_MORPHOLOGY_CACHED_STATS__
