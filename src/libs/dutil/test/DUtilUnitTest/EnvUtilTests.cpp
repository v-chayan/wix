// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.

#include "precomp.h"

using namespace System;
using namespace Xunit;
using namespace WixBuildTools::TestSupport;

namespace DutilTests
{
    public ref class EnvUtil
    {
    public:
        [Fact]
        void EnvExpandEnvironmentStringsTest()
        {
            HRESULT hr = S_OK;
            LPWSTR sczExpanded = NULL;
            SIZE_T cchExpanded = 0;
            LPCWSTR wzSimpleString = L"%USERPROFILE%";
            LPCWSTR wzMultipleString = L"%TEMP%;%PATH%";
            LPCWSTR wzLongMultipleString = L"%TEMP%;%PATH%;C:\\abcdefghijklomnopqrstuvwxyz0123456789\\abcdefghijklomnopqrstuvwxyz0123456789\\abcdefghijklomnopqrstuvwxyz0123456789\\abcdefghijklomnopqrstuvwxyz0123456789\\abcdefghijklomnopqrstuvwxyz0123456789";
            String^ expandedSimpleString = Environment::ExpandEnvironmentVariables(gcnew String(wzSimpleString));
            String^ expandedMultipleString = Environment::ExpandEnvironmentVariables(gcnew String(wzMultipleString));
            String^ expandedLongMultipleString = Environment::ExpandEnvironmentVariables(gcnew String(wzLongMultipleString));

            try
            {
                hr = EnvExpandEnvironmentStrings(wzSimpleString, &sczExpanded, &cchExpanded);
                NativeAssert::Succeeded(hr, "Failed to expand simple string.");
                WixAssert::StringEqual(expandedSimpleString, gcnew String(sczExpanded), false);
                NativeAssert::Equal<SIZE_T>(expandedSimpleString->Length + 1, cchExpanded);

                hr = EnvExpandEnvironmentStrings(wzMultipleString, &sczExpanded, &cchExpanded);
                NativeAssert::Succeeded(hr, "Failed to expand multiple string.");
                WixAssert::StringEqual(expandedMultipleString, gcnew String(sczExpanded), false);
                NativeAssert::Equal<SIZE_T>(expandedMultipleString->Length + 1, cchExpanded);

                hr = EnvExpandEnvironmentStrings(wzLongMultipleString, &sczExpanded, &cchExpanded);
                NativeAssert::Succeeded(hr, "Failed to expand long multiple string.");
                WixAssert::StringEqual(expandedLongMultipleString, gcnew String(sczExpanded), false);
                NativeAssert::Equal<SIZE_T>(expandedLongMultipleString->Length + 1, cchExpanded);
            }
            finally
            {
                ReleaseStr(sczExpanded);
            }
        }
    };
}
