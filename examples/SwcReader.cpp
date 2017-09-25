/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Author <author@urjc.es>
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

#include <nsol/nsol.h>

#include <assert.h>

#include <iostream>

#include <stack>

using namespace nsol;
using namespace std;

int main(int argc, char *argv[])
{

  SwcReader r;
  SwcWriter w;

  if ( argc < 2 )
    std::cerr << "Error: swc file parameter needed." << std::endl;

  cout << "Reading file " << argv[1] << endl;

  NeuronMorphologyPtr n = r.readMorphology(argv[1]);

  if (!n)
    return -1;

  string filename;

  cout << "Filename to export: ";
  cin >> filename;

  w.writeMorphology(filename, n);

//  cout << "Neuron loaded with " << n->numNeurites() << " neurites" << endl;

  Neurites neurites = n->neurites();

  int j = 0;
  NSOL_FOREACH( neurite, neurites )
  {
    std::cout << "  Neurite " << j << endl;;
    j++;

    int numSections = 0;
    int numNodes = 1;
    std::stack< SectionPtr > sPS;
    sPS.push( (*neurite)->firstSection( ));


    while( ! sPS.empty( ))
    {
      SectionPtr section = sPS.top( );
      sPS.pop( );
      numSections ++;

      if ( section->firstNode( ))
        numNodes += ( unsigned int ) section->nodes( ).size(  ) - 1;

      cout << "    Section-> number of nodes: "
           << section->nodes( ).size( ) << endl;
      cout << "      First Node: " << section->firstNode( )->id( )
           << " End Node: " << section->lastNode( )->id( ) << endl;

      if (section->children( ).size( ) > 0 )
        NSOL_FOREACH( sec, section->children( ))
        {
          if( section->lastNode( ) != (*sec)->firstNode( ))
            cout << "Inconherencia entre nodos" << endl;
          sPS.push( *sec );
        }
    }
    cout << " Number of sections " << numSections;
    cout << " number of nodes " << numNodes << endl;
  }

//  for (Neurites::iterator it = neurites.begin(); it != neurites.end(); ++it)
//  {
////    cout << "Neurite of type : "
////         << (((*it)->neuriteType() == Neurite::AXON) ? "axon" : "");
//
//    if ((*it)->neuriteType() == Neurite::DENDRITE)
//    {
//
////      cout
////          << "dendrite "
////          << (((*it)->asDendrite()->dendriteType() == Dendrite::APICAL) ?
////              "apical" : "basal");
//
//    }
////    cout << endl;
//
//    //    (*it)
//
//  }
//
//  for (Neurites::iterator it = neurites.begin(); it != neurites.end(); ++it)
//  {
//    NeuritePtr neurite = (*it);
//
////    cout << "######################################################" << endl;
//
////    if (neurite->hasNeuron())
////      cout << "Neurite has neuron" << endl;
////    else
////      cout << "Neurite does not have neuron" << endl;
//
//    //    SectionPtr section = neurite->firstSection();
//
//    if (!neurite->firstSection())
//    {
////      cout << "Neurite has no sections" << endl;
//      continue;
//    }
////    cout << "First section " << neurite->firstSection() << endl;
//
//    stack<SectionPtr> stack;
//    stack.push(neurite->firstSection());
//
//    while (!stack.empty())
//    {
//
//      SectionPtr section = stack.top();
//
////      cout << "Section " << section << endl;
//
//      assert(section);
//      stack.pop();
//
////      cout << "Section " << section << " parent " << section->parent()
////           << " children: ";
//
//      for (Sections::iterator itSect = section->children().begin();
//          itSect != section->children().end(); ++itSect)
//      {
//        SectionPtr child = (*itSect);
////        cout << child << " ";
//        stack.push(child);
//      };
//
////      cout << endl;
//    }
//
//    // while (section) {
//    //   cout << "Section " << section << " parent " << section->parent()
//    // 	   << " children: ";
//    //   for (Sections::iterator itSect = section->children().begin();
//    // 	   itSect != section->children().end(); itSect++) {
//    // 	SectionPtr child = (*itSect);
//    // 	cout << child << " ";
//    //   };
//    //   if (section->children().size() > 0)
//    // 	section = section->children()[0];
//    //   cout << endl;
//    // }
//
//  }
//
//  // std::cout << "Number neurite bifurcations:" << n->numNeuriteBifurcations() << std::endl;
//  // std::cout << "Number neurite branchs:" << n->numNeuriteBranches() << std::endl;
//  // std::cout << "Number dentrite branchs:" << n->numDendriteBranches() << std::endl;
//  // std::cout << "Number basal dentrites:" << n->basalDendrites()->size() << std::endl;
//  // std::cout << "Number apical dentrites:" << n->apicalDendrites()->size() << std::endl;
//  // std::cout << "Number axon branchs:" << n->numAxonBranches() << std::endl;
//  // std::cout << "Number stems:" << n->numNeurites() << std::endl;
//
//  // std::cout << "##############################################"<< std::endl;
//
//  // std::cout << "Total volume:" << n->volume() << std::endl;
//  // std::cout << "Neurites volume:" << n->neuritesVolume() << std::endl;
//  // std::cout << "Dendrites volume :" << n->dendritesVolume() << std::endl;
//  // std::cout << "Axon volume:" << n->axonVolume() << std::endl;
//  // std::cout << "Soma volume:" << n->soma().volume() << std::endl;
//
//  // std::cout << "##############################################"<< std::endl;
//
//  // std::cout << "Total surface:" << n->surface() << std::endl;
//  // std::cout << "Neurites surface:" << n->neuritesSurface() << std::endl;
//  // std::cout << "Dendrites surface:" << n->dendritesSurface() << std::endl;
//  // std::cout << "Axon surface:" << n->axonSurface() << std::endl;
//  // std::cout << "Soma surface:" << n->soma().surface() << std::endl;
//
//  std::cout << "##############################################"<< std::endl;
//
//  // std::cout << "Total lenght:" << n->length() << std::endl;
//  // std::cout << "Neurites lenght:" << n->neuritesLength() << std::endl;
//  // std::cout << "Dendrites lenght:" << n->dendritesLength() << std::endl;
//  // std::cout << "Axon lenght:" << n->axonLength() << std::endl;
//  // std::cout << "Mean radius first section:" << n->dendrites()->begin()[0]->firstSection()- << std::endl;
//  // std::cout << "Mean radius first section:"
//  //           << SectionStats::meanRadius(
//  //             n->dendrites()->begin()[0]->firstSection() )
//  //           << std::endl;
//
//
////  std::cout << "###############BORRAMOS UN SEGMENTO#############"<< std::endl;
////
////  Dendrites *dendrites = n->dendrites();
////
////  DendritePtr dendrite = dendrites->begin()[0];
////
////  dendrite->firstSection()->removeSegment(dendrite->firstSection()->_firstSegment->next());
////
////  std::cout << "Total lenght:" << n->length() << std::endl;
////  std::cout << "Neurites lenght:" << n->neuritesLength() << std::endl;
////  std::cout << "Dendrites lenght:" << n->dendritesLength() << std::endl;
////  std::cout << "Axon lenght:" << n->axonLength() << std::endl;
////
////  std::cout << "###############COLLAPSE SECTION#############"<< std::endl;
////
////  dendrite->firstSection()->fuseSection();
////
////  std::cout << "Total lenght:" << n->length() << std::endl;
////  std::cout << "Neurites lenght:" << n->neuritesLength() << std::endl;
////  std::cout << "Dendrites lenght:" << n->dendritesLength() << std::endl;
////  std::cout << "Axon lenght:" << n->axonLength() << std::endl;

  delete n;
}
