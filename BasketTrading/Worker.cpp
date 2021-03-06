/************************************************************************
 * Copyright(c) 2012, One Unified. All rights reserved.                 *
 * email: info@oneunified.net                                           *
 *                                                                      *
 * This file is provided as is WITHOUT ANY WARRANTY                     *
 *  without even the implied warranty of                                *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                *
 *                                                                      *
 * This software may not be used nor distributed without proper license *
 * agreement.                                                           *

 *                                                                      *
 * See the file LICENSE.txt for redistribution information.             *
 ************************************************************************/

// CAV.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <string>

#include <boost/ref.hpp>
#include <boost/foreach.hpp>

#include "Worker.h"

#include "SymbolSelection.h"

Worker::Worker( OnCompletionHandler f ) {
  m_OnCompletion = f;
  m_pThread = new boost::thread( boost::ref( *this ) );
}

Worker::~Worker(void) {
  delete m_pThread; 
}

void Worker::operator()( void ) {

  // last day of available data
  SymbolSelection selector( ptime( date( 2018, 9, 13 ), time_duration( 0, 0, 0 ) ) );
  selector.Process( m_setInstrumentInfo );

  std::cout << "Symbol List: " << std::endl;
  std::for_each( m_setInstrumentInfo.begin(), m_setInstrumentInfo.end(), []( const setInstrumentInfo_t::value_type& item ) { std::cout << item.sName << std::endl; } );

  if ( nullptr != m_OnCompletion ) m_OnCompletion();

}

