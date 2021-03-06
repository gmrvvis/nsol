/*
 * Copyright (c) 2014-2017 GMRV/URJC.
 *
 * Authors: Pablo Toharia <pablo.toharia@urjc.es>
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

BOOST_AUTO_TEST_CASE( test_object_with_properties )
{
  nsol::Object o;
  BOOST_CHECK( o.properties( ) ==  nullptr );

  nsol::ObjectWithProperties owp1;
  nsol::ObjectPtr owp2 = owp1.create( ); // Same as new nsol::ObjectWithProperties;

#ifdef NSOL_USE_FIRES

  BOOST_CHECK_EQUAL( owp1.properties( ), &owp1 );
  BOOST_CHECK_EQUAL( owp2->properties( ), owp2 );

  owp2->properties( )->registerProperty( "label", 3 );
  BOOST_CHECK_EQUAL(
    owp2->properties( )->getProperty( "label" ).value< int >( ), 3 );

#else
  BOOST_CHECK( owp1.properties( ) == 0 );
  BOOST_CHECK( owp2->properties( ) == 0 );
#endif

}


BOOST_AUTO_TEST_CASE( test_create_object_with_properties )
{
  nsol::ObjectWithProperties owp1;

#ifdef NSOL_USE_FIRES

  nsol::ObjectPtr o2 = new nsol::Object;
  nsol::ObjectPtr o3 = o2->create( );

  nsol::ObjectPtr owp4 = new nsol::ObjectWithProperties;
  nsol::ObjectPtr owp5 = owp4->create( );

  nsol::ObjectWithPropertiesPtr owp6 =
    dynamic_cast< nsol::ObjectWithPropertiesPtr >( owp1.create( ));

  BOOST_CHECK( o2->properties( ) == 0 );
  BOOST_CHECK( o3->properties( ) == 0 );
  BOOST_CHECK( owp4->properties( ) != 0 );
  BOOST_CHECK( owp5->properties( ) != 0 );
  BOOST_CHECK( owp6->properties( ) != 0 );


  delete o2;
  delete o3;
  delete owp4;
  delete owp5;
  delete owp6;

#endif

}



BOOST_AUTO_TEST_CASE( test_node_with_properties )
{

  class Node : public nsol::Node, public nsol::ObjectWithProperties
  {
  };

  Node node;

#ifdef NSOL_USE_FIRES

  BOOST_CHECK_EQUAL( node.properties( ), &node );

  node.properties( )->registerProperty( "label", 3.5f );
  BOOST_CHECK(
    node.properties( )->getProperty( "label" ).value< float >( ) ==
    3.5f );

  node.properties( )->registerProperty( "label2", std::string( "hello" ));
  BOOST_CHECK(
    node.properties( )->getProperty( "label2" ).value< std::string >( ) ==
    std::string( "hello" ));


#else

  BOOST_CHECK( node.properties( ) == nullptr );

#endif



}
