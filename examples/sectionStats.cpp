/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * This file is part of nsol <https://github.com/gmrvvis/nsol>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

/*
 * Example to show how to use stats and cached stats
 */

#include <nsol/nsol.h>
#include <stack>


int main ( int argc, char ** argv )
{
  std::cout << std::endl;

  if ( argc < 2 )
  {
    std::cerr << "Error. Usage: " << argv[0]
              << " swc_input_file" << std::endl;
    return -1;
  }

  std::cout << "Reading neuron without stats" << std::endl;
  nsol::SwcReader readerWithoutStats;
  nsol::NeuronPtr neuron = readerWithoutStats.readNeuron( argv[1] );

  std::cout << "Reading neuron with stats" << std::endl;
  nsol::SwcReaderStats readerWithStats;
  nsol::NeuronPtr neuronWithStats = readerWithStats.readNeuron( argv[1] );

  std::cout << "Reading neuron with cached stats" << std::endl;
  nsol::SwcReaderCachedStats readerWithCachedStats;
  nsol::NeuronPtr neuronWithCachedStats =
    readerWithCachedStats.readNeuron( argv[1] );

  if ( ! neuron || ! neuronWithStats || ! neuronWithCachedStats )
  {
    std::cerr << "Could not read neurons" << std::endl;
    return -1;
  }


  nsol::NeuronMorphologySectionPtr section =
    neuron->morphology( )->neurites( )[0]->firstSection( );

  nsol::NeuronMorphologySectionPtr sectionWithStats =
    neuronWithStats->morphology( )->neurites()[0]->firstSection( );

  nsol::NeuronMorphologySectionPtr sectionWithCachedStats =
    neuronWithCachedStats->morphology( )->neurites()[0]->firstSection( );

  if ( ! section || ! sectionWithStats || ! sectionWithCachedStats )
  {
    std::cerr << "Could not get sections of first neurite" << std::endl;
    return -1;
  }

  std::cout << std::endl;

  // Section without stats should return nullptr when asking for its stats
  NSOL_CHECK_THROW ( section->stats( ) == nullptr, "stats not null" );

  // Section without stats should return SectionStats pointer
  NSOL_CHECK_THROW ( sectionWithStats->stats( ) != nullptr, "stats null" );

  // Will get the base class to force cache operations
  nsol::NeuronMorphologySectionCachedStats * sectionCached =
    dynamic_cast< nsol::NeuronMorphologySectionCachedStats * >
    ( sectionWithCachedStats->stats( ));
  NSOL_CHECK_THROW( sectionCached, "non cached section" );


#define PRINT_SURFACE_DIRTY_STATE( section )                \
  (( section->dirty(nsol::NeuronMorphologySectionCachedStats::SURFACE) ) ?  \
   "Dirty" : "Clean" )


  std::cout << std::endl;

  std::cout << "Surface of the first section of the first neurite "
            << std::endl;

  std::cout << "\tNon cached section: "
            << sectionWithStats->stats( )->getStat(
              nsol::NeuronMorphologySectionStats::
              /*TNeuronMorphologySectionStat::*/SURFACE ) << std::endl;

  std::cout << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                         */SURFACE ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                         */SURFACE ) << std::endl;

  std::cout << std::endl;

  // Next code shows how to force dirty on a specific cached value
  sectionCached->setDirty( nsol::NeuronMorphologySectionCachedStats::SURFACE );

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                         */SURFACE ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                         */SURFACE ) << std::endl;

  std::cout << std::endl;

  // Next code shows how to force dirty on all cached values
  sectionCached->setAndPropagateDirty( );

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                         */SURFACE ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                         */SURFACE ) << std::endl;

  std::cout << std::endl;

  // Now lets pretend to change something on a segment an see if it propagates
  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                         */SURFACE ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                         */SURFACE ) << std::endl;

  std::cout << std::endl;

  // Now changind the radius of a node should dirty segment and section
  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                         */SURFACE ) << std::endl;

  std::cout << "\tCached section ("
            << PRINT_SURFACE_DIRTY_STATE( sectionCached ) << "): ";
  std::cout << sectionWithCachedStats->stats( )->getStat(
    nsol::NeuronMorphologySectionStats::/*TNeuronMorphologySectionStat::
                                         */SURFACE ) << std::endl;

  std::cout << std::endl;


  // Print stats of each neurite
  int j = 0;
  for ( const auto& neurite : neuronWithCachedStats->morphology( )->neurites( ))
  {
    std::cout << "Neurite " << j << std::endl;

    std::stack< nsol::SectionPtr > sSP;

    nsol::NeuronMorphologySectionPtr neuriteSection = neurite->firstSection( );

    sSP.push( neuriteSection );

    int k = 0;
    while ( !sSP.empty( ))
    {
      neuriteSection = dynamic_cast< nsol::NeuronMorphologySectionPtr >(
        sSP.top( ));
      sSP.pop( );

      std::cout << "  Section " << k << std::endl;
      std::cout << "    Surface " << neuriteSection->stats( )->getStat(
        nsol::NeuronMorphologySectionStats::SURFACE ) << std::endl;
      std::cout << "    Volume " << neuriteSection->stats( )->getStat(
        nsol::NeuronMorphologySectionStats::VOLUME ) << std::endl;
      std::cout << "    Length " << neuriteSection->stats( )->getStat(
        nsol::NeuronMorphologySectionStats::LENGTH ) << std::endl;


      if ( section->children( ).size( ) > 0 )
        for ( const auto& sec : section->children( ))
          sSP.push( sec );
      ++k;
    }

    ++j;
  }

  return 0;

}
