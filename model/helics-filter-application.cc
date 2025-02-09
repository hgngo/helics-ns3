#include <iostream>
#include <fstream>
#include <vector>

#include "ns3/log.h"
#include "ns3/string.h"

#include "ns3/helics.h"
#include "ns3/helics-application.h"
#include "ns3/helics-filter-application.h"
#include "helics/helics.hpp"

#include <algorithm>
#include <sstream>
#include <string>
#include <utility>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("HelicsFilterApplication");

NS_OBJECT_ENSURE_REGISTERED (HelicsFilterApplication);

TypeId
HelicsFilterApplication::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::HelicsFilterApplication")
    .SetParent<HelicsApplication> ()
    .AddConstructor<HelicsFilterApplication> ()
  ;
  return tid;
}

HelicsFilterApplication::HelicsFilterApplication ()
{
  NS_LOG_FUNCTION (this);
}

HelicsFilterApplication::~HelicsFilterApplication()
{
  NS_LOG_FUNCTION (this);
}

void
HelicsFilterApplication::DoDispose (void)
{
  NS_LOG_FUNCTION (this);

  HelicsApplication::DoDispose ();
}

void 
HelicsFilterApplication::StartApplication (void)
{
  NS_LOG_FUNCTION (this);

  HelicsApplication::StartApplication();
}

void 
HelicsFilterApplication::StopApplication (void)
{
  NS_LOG_FUNCTION (this);

  HelicsApplication::StopApplication();
}

void
HelicsFilterApplication::DoEndpoint (helics::Endpoint id, helics::Time time, std::unique_ptr<helics::Message> message)
{
  NS_LOG_FUNCTION (this << id.getName() << time << message->to_string());

  Send (message->original_dest, std::make_unique<helics::Message> (*message));
}

void
HelicsFilterApplication::DoRead (std::unique_ptr<helics::Message> message)
{
  NS_LOG_FUNCTION (this << message->to_string());

  std::swap(message->dest, message->original_dest);
  helics_federate->sendMessage (helics_endpoint, std::move (message));
}

} // Namespace ns3
