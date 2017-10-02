/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Raquel Jarillo <raquel.jarillo@urjc.es>
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

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

using namespace nsol;

BOOST_AUTO_TEST_CASE( segmentStats_stats )
{
   SegmentStats* segmentStat = new SegmentStats();

   BOOST_CHECK_EQUAL( segmentStat->stats() != nullptr, true );

   // Free dymanic memory used
   NSOL_DELETE_PTR( segmentStat );

}

BOOST_AUTO_TEST_CASE( segmentStats_getStat )
{
   {
      SegmentStats* segmentStat = new SegmentStats( );

      // Aggregation STD_DEV & VARIANCE
      const NodePtr begin_node( new Node );
      const NodePtr end_node( new Node );
      float result = segmentStat->getStat( SegmentStats::SURFACE, nullptr,
                                           nullptr );
      float result1 = segmentStat->getStat( SegmentStats::VOLUME, nullptr,
                                           nullptr );
      float result2 = segmentStat->getStat( SegmentStats::LENGTH, begin_node,
                                            end_node );
      float result3 = segmentStat->getStat( SegmentStats::RADIUS, begin_node,
                                            end_node );

      BOOST_CHECK(( result == result1 ) && ( result1 == result2 ) &&
                  ( result2 == result3 ));
      BOOST_CHECK_EQUAL( result, 0.0f );

      // Free dymanic memory used
      NSOL_DELETE_PTR( segmentStat );
   }
   {
      SegmentStats* segmentStat1 = new SegmentStats( );
      const NodePtr begin_node( new Node );
      const NodePtr end_node( new Node );

      begin_node->point( Vec3f(1.0f, 1.0f, 1.0f));
      end_node->point( Vec3f(2.0f, 3.0f, 5.0f ));

      begin_node->radius( 10.f );
      end_node->radius( 5.0f );

      float segmentLength = (begin_node->point( ) - end_node->point( )).norm( );
      float radiusDifference = begin_node->radius() - end_node->radius();
      float generatrix = sqrt( segmentLength*segmentLength +
                                 radiusDifference*radiusDifference );

      float result = ( M_PI ) * ( begin_node->radius() + end_node->radius() )
                       * generatrix;

      float result1 = segmentStat1->getStat( SegmentStats::SURFACE, begin_node,
                                               end_node );

      BOOST_CHECK_EQUAL( result, result1 );

      float result2 = (M_PI_3) * (begin_node->point( ) - end_node->point( ))
              .norm( ) * ( begin_node->radius() * begin_node->radius() +
              end_node->radius()*end_node->radius() +
              2.0f*begin_node->radius()*end_node->radius() );

      float result3 = segmentStat1->getStat( SegmentStats::VOLUME, begin_node,
                                             end_node );


      BOOST_CHECK_EQUAL( result2, result3 );

      // Free dymanic memory used
      NSOL_DELETE_PTR( segmentStat1 );

   }
}
