#ifndef __NSOL_COLUMNTEST__
#define __NSOL_COLUMNTEST__

#include <limits.h>
#include <gtest/gtest.h>

#include <Column.h>

class ColumnTest : public ::testing::Test {
 
protected:

  ColumnTest()
  {
    // You can do set-up work for each test here. 
  }

  virtual ~ColumnTest() 
  {
    // You can do clean-up work that doesn't throw exceptions here.
  }


  virtual void SetUp() 
  {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() 
  {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
};


TEST_F(ColumnTest, firstTest) 
{
  ASSERT_EQ(0,0); 
}



#endif