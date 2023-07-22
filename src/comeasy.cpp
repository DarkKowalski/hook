// # Copyright (c) Microsoft Corporation

// All rights reserved.

// # MIT License

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

//////////////////////////////////////////////////////////////////////////////
//
//  Detour Test Program (comeasy.cpp of comeasy.exe)
//
//  Microsoft Research Detours Package
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//

#include <ole2.h>
#include <windows.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
//
int __cdecl main(int argc, char **argv)
{
    HRESULT hr;

    (void)argc;
    (void)argv;

    LPSTREAM pStream = NULL;
    ULARGE_INTEGER ul;
    LARGE_INTEGER li;

    printf("comeasy.exe: Starting (at %p).\n", main);

    CoInitialize(NULL);

    hr = CreateStreamOnHGlobal(NULL, TRUE, &pStream);

    ul.QuadPart = 512;
    hr = pStream->SetSize(ul);

    li.QuadPart = 0;
    hr = pStream->Seek(li, STREAM_SEEK_SET, NULL);

    printf("comeasy.exe: First write.\n");
    fflush(stdout);

    li.QuadPart = 0;
    hr = pStream->Write(&ul, sizeof(ul), NULL);

    printf("comeasy.exe: Second write.\n");
    fflush(stdout);

    li.QuadPart = 1;
    hr = pStream->Write(&li, sizeof(li), NULL);

    printf("comeasy.exe: Third write.\n");
    fflush(stdout);

    li.QuadPart = 2;
    hr = pStream->Write(&li, sizeof(li), NULL);

    pStream->Release();
    pStream = NULL;

    CoUninitialize();

    printf("comeasy.exe: Exiting.\n\n");
    fflush(stdout);

    return 0;
}

//
///////////////////////////////////////////////////////////////// End of File.
