/**
* Digital Voice Modem - Common Library
* GPLv2 Open Source. Use is subject to license terms.
* DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
*
* @package DVM / Common Library
*
*/
//
// Based on code from the CRUD project. (https://github.com/venediktov/CRUD)
// Licensed under the BPL-1.0 License (https://opensource.org/license/bsl1-0-html)
//
/*
*   Copyright (c) 2003-2013 Christopher M. Kohlhoff
*   Copyright (C) 2023 by Bryan Biedenkapp N2PLL
*
*   Permission is hereby granted, free of charge, to any person or organization
*   obtaining a copy of the software and accompanying documentation covered by
*   this license (the “Software”) to use, reproduce, display, distribute, execute,
*   and transmit the Software, and to prepare derivative works of the Software, and
*   to permit third-parties to whom the Software is furnished to do so, all subject
*   to the following:
*
*   The copyright notices in the Software and this entire statement, including the
*   above license grant, this restriction and the following disclaimer, must be included
*   in all copies of the Software, in whole or in part, and all derivative works of the
*   Software, unless such copies or derivative works are solely in the form of
*   machine-executable object code generated by a source language processor.
*
*   THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
*   INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
*   PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR ANYONE
*   DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN
*   CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
*   OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#if !defined(__REST_HTTP__HTTP_HEADERS_H__)
#define __REST_HTTP__HTTP_HEADERS_H__

#include "common/Defines.h"
#include "common/Log.h"
#include "common/Utils.h"

#include <string>
#include <vector>

namespace network
{
    namespace rest
    {
        namespace http
        {

            // ---------------------------------------------------------------------------
            //  Class Prototypes
            // ---------------------------------------------------------------------------

            struct HTTPPayload;

            // ---------------------------------------------------------------------------
            //  Structure Declaration
            //
            // ---------------------------------------------------------------------------

            struct HTTPHeaders {
                struct Header
                {
                    std::string name;
                    std::string value;

                    Header() : name{}, value{} { /* stub */}
                    Header(std::string n, std::string v) : name{n}, value{v} { /* stub */ }
                };

                /// <summary>Gets the list of HTTP headers.</summary>
                std::vector<Header> headers() const { return m_headers; }
                /// <summary>Returns true if the headers are empty.</summary>
                bool empty() const { return m_headers.empty(); }
                /// <summary>Returns the number of headers.</summary>
                std::size_t size() const { return m_headers.size(); }
                /// <summary>Clears the list of HTTP headers.</summary>
                void clearHeaders() { m_headers = std::vector<Header>(); }
                /// <summary>Helper to add a HTTP header.</summary>
                void add(const std::string& name, const std::string& value)
                {
                    //::LogDebug(LOG_REST, "HTTPHeaders::add(), header = %s, value = %s", name.c_str(), value.c_str());
                    for (auto& header : m_headers) {
                        if (::strtolower(header.name) == ::strtolower(name)) {
                            header.value = value;
                            return;
                        }
                    }

                    m_headers.push_back(Header(name, value));
                    //for (auto header : m_headers)
                    //    ::LogDebug(LOG_REST, "HTTPHeaders::add() m_headers.header = %s, m_headers.value = %s", header.name.c_str(), header.value.c_str());
                }
                /// <summary>Helper to add a HTTP header.</summary>
                void remove(const std::string headerName)
                {
                    auto header = std::find_if(m_headers.begin(), m_headers.end(), [&](const Header& h) {
                        return ::strtolower(h.name) == ::strtolower(headerName);
                    });

                    if (header != m_headers.end()) {
                        m_headers.erase(header);
                    }
                }
                /// <summary>Helper to find the named HTTP header.</summary>
                std::string find(const std::string headerName) const
                {
                    auto header = std::find_if(m_headers.begin(), m_headers.end(), [&](const Header& h) {
                        return ::strtolower(h.name) == ::strtolower(headerName);
                    });

                    if (header != m_headers.end()) {
                        return header->value;
                    }
                    else {
                        return "";
                    }
                }

            private:
                friend struct HTTPPayload;
                std::vector<Header> m_headers;
            };
        } // namespace http
    } // namespace rest
} // namespace network

#endif // __REST_HTTP__HTTP_HEADERS_H__
