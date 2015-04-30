/**
 * @file    NeuronMorphologyStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_NEURON_MORPHOLOGY_STATS__
#define __NSOL_NEURON_MORPHOLOGY_STATS__

#include "../NeuronMorphology.h"

namespace nsol
{

  /** \class NeuronMorphologyStats
   *  \brief This class allows to compute stats for sections
   *
   *  Using this class instead of NeuronMorphology when constructing the
   *  hierarchy allows to call the method stats from base NeuronMorphology
   *  class and get the corresponding volume, surface and length.
   *
   * Example: @include examples/neuronStats.cpp
   */
  class NeuronMorphologyStats
    : public NeuronMorphology
  {

  public:

    typedef enum
    {
      // Volume
      DENDRITIC_VOLUME,
      AXON_VOLUME,
      NEURITIC_VOLUME,
      SOMA_VOLUME,
      VOLUME,
      // Surface
      DENDRITIC_SURFACE,
      AXON_SURFACE,
      NEURITIC_SURFACE,
      SOMA_SURFACE,
      SURFACE,
      // Length
      DENDRITIC_LENGTH,
      AXON_LENGTH,
      NEURITIC_LENGTH,
      // Bifurcations
      DENDRITIC_BIFURCATIONS,
      AXON_BIFURCATIONS,
      NEURITIC_BIFURCATIONS,
      NEURON_MORPHOLOGY_NUM_STATS
    } TNeuronMorphologyStat;

    NeuronMorphologyStats( SomaPtr soma_ )
      : NeuronMorphology( soma_ )
    {
    }

    /**
     * Returns object as NeuronMorphologyStats
     * @return pointer to NeuronMorphologyStats object
     */
    NSOL_API
    virtual NeuronMorphologyStats * stats( void );


    virtual float getStat( TNeuronMorphologyStat stat,
                           TAggregation agg = TAggregation::TOTAL ) const;


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

    // NSOL_API
    // virtual float somaSurface( void ) const;

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

  }; // class NeuronMorphologyStats

} // namespace nsol

#endif // __NSOL_NEURON_MORPHOLOGY_STATS__