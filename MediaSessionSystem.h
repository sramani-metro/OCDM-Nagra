/*
 * Copyright 2018 Metrological
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "cdmi.h"

namespace CDMi {

class MediaSessionSystem : public IMediaSessionSystem {
public:
    enum request {
        FILTERS      = 0x0001,
        KEYREADY     = 0x0002,
        KEYNEEDED    = 0x0004,
        RENEWAL      = 0x0008,
        RENEWALREADY = 0x0010,
        EMMDELIVERY  = 0x0020
    };

public:
    //static const std::vector<std::string> m_mimeTypes;

    MediaSessionSystem(const uint8_t *f_pbInitData, uint32_t f_cbInitData);
    ~MediaSessionSystem();

    // IMediaSessionSystem overrides
    virtual void Run(const IMediaKeySessionCallback *callback) override;
    virtual void Update( const uint8_t *response, uint32_t responseLength) override;
    virtual CDMi_RESULT Load() override;
    virtual CDMi_RESULT Remove() override;
    virtual CDMi_RESULT Close() override;
    virtual const char *GetSessionId() const override;
    virtual const char *GetKeySystem() const override;
    virtual CDMi_RESULT Decrypt(
        const uint8_t *f_pbSessionKey,
        uint32_t f_cbSessionKey,
        const uint32_t *f_pdwSubSampleMapping,
        uint32_t f_cdwSubSampleMapping,
        const uint8_t *f_pbIV,
        uint32_t f_cbIV,
        const uint8_t *f_pbData,
        uint32_t f_cbData,
        uint32_t *f_pcbOpaqueClearContent,
        uint8_t **f_ppbOpaqueClearContent,
        const uint8_t keyIdLength,
        const uint8_t* keyId);
    virtual CDMi_RESULT ReleaseClearContent(
        const uint8_t *f_pbSessionKey,
        uint32_t f_cbSessionKey,
        const uint32_t  f_cbClearContentOpaque,
        uint8_t  *f_pbClearContentOpaque );

private:
    static void OnRenewal(void* appSession);
    static void OnNeedKey(void* appSession);
    static void OnDeliveryCompleted(void* deliverySession);

    void OnNeedKey(void* dsmSession, void* content) {
    void OnRenewal();
    void OnDelivery();

    std::string CreateRenewalExchange();

private:
    std::string _sessionId;
    IMediaSessionSystemCallback* _callback;
    void* _applicationSession;
    uint32_t _requests;
    void* _applicationSession;
    void* _inbandSession;
    void* _deliverySession;
    std::string _renewelChallenge;
    std::String _keyNeededChallenge;
    std::String _filters;
};

} // namespace CDMi