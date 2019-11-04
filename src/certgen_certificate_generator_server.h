/*  =========================================================================
    certgen_certificate_generator_server - class description

    Copyright (C) 2014 - 2019 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#ifndef CERTGEN_CERTIFICATE_GENERATOR_SERVER_H_INCLUDED
#define CERTGEN_CERTIFICATE_GENERATOR_SERVER_H_INCLUDED

#include <functional>
#include <fty_common_sync_server.h>

namespace certgen
{
    using Command   = std::string;

    using FctCommandHandler = std::function<std::string (const std::vector<std::string> &)>;

    class CertificateGeneratorServer final : public fty::SyncServer
    {
        public:
            explicit CertificateGeneratorServer();
            fty::Payload handleRequest(const fty::Sender & sender, const fty::Payload & payload) override;

        private:
            // List of supported commands with a reference to the handler for this command.
            std::map<Command, FctCommandHandler> m_supportedCommands;

            // Handlers for all supported commands
            std::string handleGenerateSelfsignedCertificate(const fty::Payload & params);
            std::string handleGenerateCSR(const fty::Payload & params);
            std::string handleImportCertificate(const fty::Payload & params);

        public:
            //Command list
            static constexpr const char* GENERATE_SELFSIGNED_CERTIFICATE = "GENERATE_SELFSIGNED_CERTIFICATE";
            static constexpr const char* GENERATE_CSR = "GENERATE_CSR";
            static constexpr const char* IMPORT_CERTIFICATE = "IMPORT_CERTIFICATE";
    };

} // namescpace certgen


#endif
