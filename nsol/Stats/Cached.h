/**
 * @file    Cached.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
            Do not distribute without further notice.
*/
#ifndef __NSOL_STATS_CACHED__
#define __NSOL_STATS_CACHED__

#include "../error.h"

#include <map>

namespace nsol
{
  /*! \class Cached
    \brief This class allows to cache values


  */
  template < typename TYPE = float > class Cached
  {

  public:

    Cached( void )
    {
    }

    virtual ~Cached( void )
    {
    }

    bool dirty( unsigned int id ) const
    {
      return ( _values.find( id ) == _values.end( ));
    }

    void setDirty( unsigned int id )
    {
      _values.erase( id );
    }

    void setDirty( void )
    {
      _values.clear( );
    }

    virtual void setAndPropagateDirty( unsigned int id )
    {
      this->setDirty( id );
      // Note: propagation has to be reimplemented if needed
    }

    virtual void setAndPropagateDirty( void )
    {
      this->setDirty( );
      // Note: propagation has to be reimplemented if needed
    }

    // This method is const to be able to cache values from 
    // derived const methods
    void cacheValue( const unsigned int id_, TYPE & value_ ) const
    {
      _values[ id_ ] = value_;
    }

    TYPE getValue( const unsigned int id_ ) const
    {
      return _values[ id_ ];
    }


  protected:

    //! Container of the cached values
    mutable std::map < unsigned int, TYPE > _values;

  };

} // namespace nsol

#endif // __NSOL_STATS_CACHED__
