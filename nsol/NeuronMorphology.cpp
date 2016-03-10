/**
 * @file    NeuronMorphology.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "NeuronMorphology.h"

namespace nsol
{

  NeuronMorphology::NeuronMorphology( void )
    : _soma( nullptr )
  {

  }

  NeuronMorphology::NeuronMorphology( SomaPtr soma_ )
    : _soma( soma_ )
  {

  }

  NeuronMorphology::~NeuronMorphology( void )
  {
  }

  SomaPtr
  NeuronMorphology::soma( SomaPtr soma_ )
  {
    NSOL_DEBUG_CHECK( soma_, "soma is null" );
    _soma = soma_;
    return soma_;
  }

  NeuritePtr
  NeuronMorphology::addNeurite( NeuritePtr neurite_ )
  {
    NSOL_DEBUG_CHECK( neurite_, "neurite is null" );
    _neurites.push_back( neurite_ );
    return neurite_;
  }

  Dendrites * NeuronMorphology::dendrites( void ) const
  {
    Dendrites * tmpDendrites = new Dendrites;

    NSOL_CONST_FOREACH( it, _neurites )
    {

      DendritePtr dend = NSOL_DYNAMIC_CAST( Dendrite, *it );

      if ( dend )
        tmpDendrites->push_back( dend );
    }
    return tmpDendrites;
  }

  Dendrites * NeuronMorphology::basalDendrites(void) const
  {

    Dendrites * tmpDendrites = new Dendrites;

    for (Neurites::const_iterator it = _neurites.begin( );
         it != _neurites.end( ); ++it)
    {
      DendritePtr dend = NSOL_DYNAMIC_CAST( Dendrite, *it );
      if ( dend &&
           ( dend->dendriteType( ) == Dendrite::BASAL ))
        tmpDendrites->push_back( dend );
    }

    return tmpDendrites;
  }

  Dendrites * NeuronMorphology::apicalDendrites( void ) const
  {
    Dendrites * tmpDendrites = new Dendrites;

    for (Neurites::const_iterator it = _neurites.begin( );
         it != _neurites.end( ); ++it)
    {
      DendritePtr dend = NSOL_DYNAMIC_CAST ( Dendrite, *it );
      if ( dend &&
           ( dend->dendriteType( ) == Dendrite::APICAL ))
        tmpDendrites->push_back( dend );
    }

    return tmpDendrites;
  }

  DendritePtr NeuronMorphology::apicalDendrite( void ) const
  {
    for (Neurites::const_iterator it = _neurites.begin( );
         it != _neurites.end( ); ++it)
    {
      DendritePtr dend = NSOL_DYNAMIC_CAST( Dendrite, *it );
      if ( dend &&
           ( dend->dendriteType( ) == Dendrite::APICAL ))
        return dend;
    }

    return nullptr;
  }

  AxonPtr NeuronMorphology::axon( void ) const
  {
    for ( const auto& neurite : _neurites )
    {
      auto axon_ = NSOL_DYNAMIC_CAST( Axon, neurite );
      if ( axon_ )
        return axon_;
    }
    return nullptr;
  }


  Neurites & NeuronMorphology::neurites( void )
  {
    return _neurites;
  }

  const Neurites & NeuronMorphology::neurites( void ) const
  {
    return _neurites;
  }

  Neurons & NeuronMorphology::parentNeurons( void )
  {
    return _parentNeurons;
  }

  const Neurons & NeuronMorphology::parentNeurons( void ) const
  {
    return _parentNeurons;
  }

  void NeuronMorphology::addParentNeuron( NeuronPtr neuron )
  {
    Neurons::iterator neuronIt =
      std::find ( _parentNeurons.begin( ),
                  _parentNeurons.end( ),
                  neuron );

    if ( neuronIt != _parentNeurons.end( ))
      _parentNeurons.push_back( neuron );


  }

  SomaPtr NeuronMorphology::soma( void )
  {
    return _soma;
  }


} // namespace nsol

// EOF
