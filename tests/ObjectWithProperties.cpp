/*
 * @brief   Test for class nsol::ObjectWithProperties
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
 */

#include <limits.h>
#include <nsol/nsol.h>
#include "nsolTests.h"

BOOST_AUTO_TEST_CASE( test_object_with_properties )
{
  nsol::Object o;
  BOOST_CHECK( o.properties( ) ==  nullptr );

  nsol::ObjectWithProperties owp1;
  nsol::ObjectPtr owp2 = new nsol::ObjectWithProperties;

#ifdef NSOL_WITH_FIRES

  BOOST_CHECK_EQUAL( owp1.properties( ), &owp1 );
  BOOST_CHECK_EQUAL( owp2->properties( ), owp2 );

  owp2->properties( )->registerFeature( "label", 3 );
  BOOST_CHECK_EQUAL(
    owp2->properties( )->getFeature( "label" ).value< int >( ), 3 );

#else
  BOOST_CHECK( owp2->properties( ) == nullptr );
  BOOST_CHECK( owp2->properties( ) == nullptr );
#endif

}


BOOST_AUTO_TEST_CASE( test_node_with_properties )
{

  class Node : public nsol::Node, public nsol::ObjectWithProperties
  {
  };

  Node node;

#ifdef NSOL_WITH_FIRES

  BOOST_CHECK_EQUAL( node.properties( ), &node );

#else

  BOOST_CHECK_EQUAL( node.properties( ), 0 );

#endif

}
