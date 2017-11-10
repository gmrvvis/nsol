/*
 * Copyright ( c ) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
 *          Ricardo Suarez
 *          Fernando Lucas Pérez
 *          Iago Calvo Lista
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
#ifndef __NSOL_SWC_READER__
#define __NSOL_SWC_READER__


#include "../Neuron.h"
#include "../Stats/NodeCached.h"
#include "../Stats/SectionCachedStats.h"
#include "../Stats/DendriteCachedStats.h"
#include "../Stats/AxonCachedStats.h"
#include "../Stats/NeuronMorphologyCachedStats.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

#include <map>
#include <stack>

namespace nsol
{

#define SWC_READER_TEMPLATE_CLASSES              \
    class NODE,                                  \
    class SECTION,                               \
    class DENDRITE,                              \
    class AXON,                                  \
    class SOMA,                                  \
    class NEURONMORPHOLOGY,                      \
    class NEURON

#define SWC_READER_TEMPLATE_CLASS_NAMES         \
    NODE,                                       \
    SECTION,                                    \
    DENDRITE,                                   \
    AXON,                                       \
    SOMA,                                       \
    NEURONMORPHOLOGY,                           \
    NEURON


  template < SWC_READER_TEMPLATE_CLASSES >
  class SwcReaderTemplated
  {

  public:

    /**
     * Creates a new Neuron that contains the NeuronMorphology described in
     * SWC file
     * Overloaded method for char* fileName, calls equivalent std::string method
     *
     * @param fileName path to SWC file to read
     * @param reposition_ sets soma center to ( 0.0, 0.0, 0.0 ) if true
     * @return pointer to the Neuron created; nullptr if failure on SWC read
     */
    NeuronPtr readNeuron( const char *fileName,
                          bool reposition_ = false );

    /**
     * Creates a new Neuron that contains the NeuronMorphology described in
     * SWC file
     * Calls readMorphology( 2 )
     *
     * @param fileName path to SWC file to read
     * @param reposition_ sets soma center to ( 0.0, 0.0, 0.0 ) if true
     * @return pointer to the Neuron created; nullptr if failure on SWC read
     */
    NeuronPtr readNeuron( const std::string fileName,
                          bool reposition_ = false );

    /**
     * Creates a NeuronMorphology and loads info described in SWC file
     * Overloaded method for char* fileName, calls equivalent std::string method
     *
     * @param fileName path to SWC file to read
     * @param reposition_ sets soma center to ( 0.0, 0.0, 0.0 ) if true
     * @return pointer to the NeuronMorphology created; nullptr if failure on SWC read
     */
    NeuronMorphologyPtr readMorphology( const char *fileName,
                                        bool reposition_ = false );

    /**
     * Creates a NeuronMorphology and loads info described in SWC file
     *
     * @param fileName path to SWC file to read
     * @param reposition_ sets soma center to ( 0.0, 0.0, 0.0 ) if true
     * @return pointer to the NeuronMorphology created; nullptr if failure on SWC read
     */
    NeuronMorphologyPtr readMorphology( const std::string fileName,
                                        bool reposition_ = false );


  protected:

    //! SWC element types
    typedef enum
    {
        SWC_SOMA = 1,
        SWC_AXON = 2,
        SWC_BASAL = 3,
        SWC_APICAL = 4
    } TSwcNodeType;

    //! Contains processed information of an SWC line element
    typedef struct
    {
      unsigned int id;
      unsigned int type;
      Vec3f xyz;
      float radius;
      int parent;
      std::vector<unsigned int> children;
    } TSwcLine;

    //! Auxiliary elements to read branching neurite sections
    typedef struct
    {
      unsigned int id;
      SectionPtr parent;
    } TReadNeuriteStackElem;


    /**
     * Reads a Neurite from a processed SWC file, calls _ReadSection
     *
     * @param d neuritePtr where info will be loaded
     * @param lines processed SWC file line information stored as map
     * @param initId node ID of the first node in the neurite to read
     * @param nodes_ auxiliary vector for recalculation purposes
     * @param reposition_ sets soma center to ( 0.0, 0.0, 0.0 ) if true;
     * it will only serve to add all new nodes to nodes_ for later
     * recalculation
     */
    void _ReadNeurite( NeuritePtr d,
                       std::map<unsigned int, TSwcLine> & lines,
                       unsigned int initId,
                       NsolVector<NodePtr>* nodes_ = nullptr,
                       bool reposition_ = false );


    /**
     * Creates and calculates sections, as well as bifurcation and branch
     * counts
     *
     * @param d pointer to Neurite where section is located
     * @param s pointer to Section where data will be loaded
     * @param n pointer to first Node in section
     * @param sectionFirstNodes pointer to stack where new first nodes
     * for new sections found will be stored
     * @param lines processed SWC file line information stored as map
     * @param nodes_ auxiliary vector for recalculation purposes
     * @param reposition_ sets soma center to ( 0.0, 0.0, 0.0 ) if true;
     * it will only serve to add all new nodes to nodes_ for later
     * recalculation
     */
    void _ReadSection( NeuritePtr d,
                      SectionPtr s,
                      NodePtr n,
                      std::stack<TReadNeuriteStackElem>* sectionFirstNodes,
                      std::map<unsigned int, TSwcLine>& lines,
                      NsolVector<NodePtr>* nodes_,
                      bool reposition_ );

  }; // class SwcReaderTemplated


  typedef SwcReaderTemplated< Node,
                              Section,
                              Dendrite,
                              Axon,
                              Soma,
                              NeuronMorphology,
                              Neuron > SwcReader;

  typedef SwcReaderTemplated< Node,
                              SectionStats,
                              DendriteStats,
                              AxonStats,
                              SomaStats,
                              NeuronMorphologyStats,
                              Neuron > SwcReaderStats;

  typedef SwcReaderTemplated< NodeCached,
                              SectionCachedStats,
                              DendriteCachedStats,
                              AxonCachedStats,
                              SomaStats,
                              NeuronMorphologyCachedStats,
                              Neuron > SwcReaderCachedStats;


  //////////////////////////////////////////////////////////////////
  //
  // Implementation of methods for SwcTemplated
  //
  //////////////////////////////////////////////////////////////////

  template < SWC_READER_TEMPLATE_CLASSES >
  NeuronPtr
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::readNeuron( 
      const char* fileName, bool reposition_ )
  {
    return this->readNeuron( std::string( fileName ), reposition_ );
  }


  template < SWC_READER_TEMPLATE_CLASSES >
  NeuronPtr
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::readNeuron( 
      const std::string fileName, bool reposition_ )
  {
    NeuronMorphologyPtr nm = this->readMorphology( std::string( fileName ),
                                                   reposition_ );

    if ( nm )
    {
      NeuronPtr neuron( new NEURON( nm ) );
      nm->addParentNeuron( neuron );
      return neuron;
    }
    else
      return nullptr;
   }


  template < SWC_READER_TEMPLATE_CLASSES >
  NeuronMorphologyPtr
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::readMorphology( 
      const char* fileName, bool reposition_ )
  {
    return this->readMorphology( std::string( fileName ), reposition_ );
  }


  template < SWC_READER_TEMPLATE_CLASSES >
  NeuronMorphologyPtr
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::readMorphology( 
      const std::string fileName, bool reposition_ )
  {
    std::ifstream inFile;
    inFile.open( fileName, std::ios::in );

    //! Opening file check
    if ( ( inFile.rdstate( ) & std::ifstream::failbit ) != 0 )
    {
      std::cerr << "Error opening file: " << fileName << std::endl;

      return nullptr;

    }

    std::string lineString;

    NsolVector< NodePtr > repositionNodes;
    NeuronMorphologyPtr neuronMorphology( new NEURONMORPHOLOGY( new SOMA ) );

    std::map<unsigned int, TSwcLine> lines;

    int lineCount = 0;

    //! Reads file, line by line
    while ( std::getline( inFile, lineString ) )
    {
      lineCount++;
      //! Trims whitespaces before first character
      lineString.erase( 0, lineString.find_first_not_of( " \r\t" ) );

      if ( lineString[0] != '#' )
      {
        //! Trims trailing whitespaces
        lineString.erase( lineString.find_last_not_of( " \r\t" ) + 1 );

        //! Verifies there are 7 fields ( or more, if comments are present )
        unsigned int fields =
            1 + ( unsigned int )std::count_if( lineString.begin( ), lineString.end( ),
                                             []( unsigned char c )
                                             {
                                               return std::isspace( c );
                                             } );

        if ( fields < 7 )
        {
          Log::log( std::string( "Skipping lineString " ) +
                    std::to_string( lineCount ) +
                    std::string( " in file " ) +
                    fileName  +std::string( ": \"" )+ lineString+
                    std::string( "\" ( not enough fields found )" ),
                    LOG_LEVEL_WARNING );
        }
        else
        {
          //! Loads info in struct TSwcLine
          std::istringstream iss( lineString );
          TSwcLine swcLineString;

          bool failed = false;
          iss >> swcLineString.id;
          if ( iss.fail( ) )
            failed = true;
          iss >> swcLineString.type;
          if ( iss.fail( ) )
            failed = true;
          iss >> swcLineString.xyz[0]
              >> swcLineString.xyz[1]
              >> swcLineString.xyz[2];
          if ( iss.fail( ) )
            failed = true;
          iss >> swcLineString.radius;
          if ( iss.fail( ) )
            failed = true;
          iss >> swcLineString.parent;
          if ( iss.fail( ) )
            failed = true;

          if ( failed )
          {
            Log::log( std::string( "Skipping lineString " ) +
                      std::to_string( lineCount ) +
                      std::string( " in file " ) +
                      fileName  +std::string( ": \"" )+ lineString+
                      std::string( "\" ( line format not recognised )" ),
                      LOG_LEVEL_WARNING );
          } else {
            lines[swcLineString.id] = swcLineString;
          }

        }
      }
    }

    inFile.close( );

    //! Adds children to TSwcLine elements created
    for ( const auto& line : lines )
    {
      if ( line.second.parent != -1 )
        lines[line.second.parent].children.push_back( line.first );
    }

    std::vector<unsigned int> somaChildren;
    std::map<unsigned int, NodePtr > nodeSomaPtr;

    //! Adds soma nodes to neuronMorphology->Soma
    for ( const auto& line : lines )
    {
      if ( line.second.type == SWC_SOMA )
      {
        NodePtr node( 
          new NODE( line.second.xyz, line.second.id, line.second.radius ) );

        /**
         * Adds nodes for later recalculation of position
         * if reposition_ is active
         */
        if ( reposition_ )
          repositionNodes.push_back( node );

        neuronMorphology->soma( )->addNode( node );

        nodeSomaPtr[line.second.id] = node;

        //! Adds non-soma childrens of soma nodes to vector for later use
        for ( const unsigned int child : line.second.children )
          if ( lines[child].type != SWC_SOMA )
            somaChildren.push_back( child );

      }
    }

    //! Initiates read process for each neurite, via first node
    for ( const unsigned int firstNodeId : somaChildren )
    {

      switch ( lines[firstNodeId].type )
      {
        case SWC_BASAL:
          DendritePtr basD;
          basD = new DENDRITE( Dendrite::BASAL );
          neuronMorphology->addNeurite( basD );
          basD->morphology( neuronMorphology );
          _ReadNeurite( basD, lines, firstNodeId,
                        &repositionNodes, reposition_ );
          break;

        case SWC_APICAL:
          /*Dendrite::TDendriteType dType =
            ( lines[firstNodeId].type == SWC_BASAL )?
            Dendrite::BASAL : Dendrite::APICAL;*/
          DendritePtr apD;
          apD = new DENDRITE( Dendrite::APICAL );
          neuronMorphology->addNeurite( apD );
          apD->morphology( neuronMorphology );
          _ReadNeurite( apD, lines, firstNodeId,
                       &repositionNodes, reposition_ );
          break;

        case SWC_AXON:
          AxonPtr nP;
          nP = new AXON( );
          neuronMorphology->addNeurite( nP );
          nP->morphology( neuronMorphology );
          _ReadNeurite( nP, lines, firstNodeId,
                       &repositionNodes, reposition_ );
          break;

        default:
          std::cerr << "Unexpected line type value in line "
                    << std::to_string( firstNodeId ) << std::endl;

      }
    }

    /**
     * Moves soma center to ( 0.0, 0.0, 0.0 ) if reposition_ is active,
     * accordingly recalculating position for all nodes
     */

    if ( reposition_ )
    {
      Vec3f center = neuronMorphology->soma( )->center( );

      NSOL_FOREACH( node, repositionNodes )
      {
        ( *node )->point( ( *node )->point( ) - center );
      }

      neuronMorphology->soma( )->center( Vec3f( 0.0f, 0.0f, 0.0f ) );

    }

    return neuronMorphology;

  }


  template < SWC_READER_TEMPLATE_CLASSES > void
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::_ReadNeurite( 
      NeuritePtr d,
      std::map<unsigned int, TSwcLine>& lines,
      unsigned int initId,
      NsolVector<NodePtr>* nodes_,
      bool reposition_ )
  {
    std::stack<TReadNeuriteStackElem> sectionFirstNodes;
    SectionPtr s = nullptr;

    s = SectionPtr( new SECTION );

    s->neurite( d );
    s->parent( NULL );

    NodePtr node;
    //! Creates first Node in first Secion
    node = new NODE( lines[initId].xyz, initId, lines[initId].radius );
    s->firstNode( node );
    //! Loads first Section in Neurite
    _ReadSection( d, s, node, &sectionFirstNodes, lines, nodes_, reposition_ );
    d->firstSection( s );

    //! Creates and loads all Sections in Neurite
    while ( !sectionFirstNodes.empty( ) )
    {
      unsigned int id = sectionFirstNodes.top( ).id;
      SectionPtr parentSection = sectionFirstNodes.top( ).parent;
      s = SectionPtr( new SECTION );
      s->neurite( d );
      s->parent( parentSection );
      sectionFirstNodes.pop( );

      //! Creates first Node of new Section
      node = new NODE( lines[id].xyz, id, lines[id].radius );
      s->addNode( node ); //

      parentSection->addChild( s );

      //! Loads Section and stores first Nodes of other Sections to load
      _ReadSection( d, s, node, &sectionFirstNodes,
                    lines, nodes_, reposition_ );

    }
  }

  template < SWC_READER_TEMPLATE_CLASSES > void
  SwcReaderTemplated< SWC_READER_TEMPLATE_CLASS_NAMES >::_ReadSection(
      NeuritePtr d,
      SectionPtr s,
      NodePtr n,
      std::stack<TReadNeuriteStackElem>* sectionFirstNodes,
      std::map<unsigned int, TSwcLine>& lines,
      NsolVector<NodePtr>* nodes_,
      bool reposition_ )
  {
    unsigned int nodeId = (unsigned int) n->id();
    //! Stores first node for later position recalculation
    if ( reposition_ )
      nodes_->push_back( n );

    //! Loads all nodes in section
    while ( lines[nodeId].children.size( ) == 1 )
    {
      nodeId = lines[nodeId].children[0];
      n = new NODE( lines[nodeId].xyz, nodeId, lines[nodeId].radius );

      //! Stores nodes for later position recalculation
      if ( reposition_ )
        nodes_->push_back( n );

      s->addNode( n );
    }

    /**
     * End of section reached;
     * first nodes of branching sections will be added to stack
     */
    if ( lines[nodeId].children.size( ) > 1 )
    {
      //! Branch count updated
      d->_addBranchCount( ( unsigned int ) lines[nodeId].children.size( ) );
      //! Plus new bifurcation
      d->_addBifurcationCount( 1 );

      //! Adds first nodes of new branches to stack
      NSOL_CONST_FOREACH( it, lines[nodeId].children )
      {
        TReadNeuriteStackElem tmpStackElem = { ( *it ), s };
        sectionFirstNodes->push( tmpStackElem );
      }

    }
  }
} // namespace nsol

#endif
