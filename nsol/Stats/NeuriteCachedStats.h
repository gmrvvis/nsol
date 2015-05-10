/**
 * @file    NeuriteCachedStats.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __NSOL_NEURITE_CACHED_STATS__
#define __NSOL_NEURITE_CACHED_STATS__

#include <nsol/api.h>

#include "Cached.h"
#include "NeuriteStats.h"

namespace nsol
{

  /** \class NeuriteCachedStats
   *  \brief This class allows to cache the stats for neurites
   *
   *  Using this class instead of Neurite or NeuriteStats when constructing
   *  the hierarchy allows to call the method stats from base Neurite
   *  class and get the corresponding volume, surface and length. If the
   *  cached value is dirty then the actual computation process is done.
   *  In case is clean the cached value is returned directly.
   *
   *  Example: @include examples/neuriteStats.cpp
   */
  class NeuriteCachedStats
    : public virtual NeuriteStats
    , public Cached<>
  {


  public:

    /**
     * Default constructor
     */
    NSOL_API
    NeuriteCachedStats( TNeuriteType neuriteType = DENDRITE );

    /**
     * Default destructor
     */
    NSOL_API
    virtual ~NeuriteCachedStats( void );

    /**
     * Set dirty a cached stat and propagates dirty to parent neurite
     * @param id identifier of the property to set dirty. It also propagates
     * dirty state to parent neurite. id value has to be one from
     * TNeuriteCachedValues (checked only on debug compiling).
     */
    NSOL_API
    virtual void setAndPropagateDirty( unsigned int id );

    /**
     * Set dirty all cached stats and propagates dirty to parent neurite
     */
    NSOL_API
    virtual void setAndPropagateDirty( void );

    /**
     * Set dirty all cached stats and propagates dirty to parent neurite
     */
    NSOL_API
    virtual void firstSection( SectionPtr section );


    /**
     * Returns the stat given if the cache is clean and if it is dirty
     * then computes the stat and stores the value in the cache. Only
     * TAggregation::TOTAL caches values, other aggregations are computed
     * @param stat stat to compute
     * @param agg aggregation used
     * @return stat value using the aggregation given
     */
    NSOL_API
    virtual float getStat( TNeuriteStat stat,
                           TAggregation agg = /*TAggregation::*/TOTAL ) const;


  }; // class NeuriteCachedStats

} // namespace nsol

#endif // __NSOL_NEURITE_CACHED_STATS__
