/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
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

#ifndef __CBOR_STRING_H__
#define __CBOR_STRING_H__

#include "cborg/CborBase.h"

#include <stdint.h>
#include <cstddef>

#include <stdio.h>


class CborString : public CborBase
{
public:

    template <std::size_t I>
    CborString(const char (&pointer)[I])
        :   CborBase(TypeString, TypeUndefined),
            string(pointer),
            length(I - 1)
    {}

    CborString(const char* pointer, uint32_t stringLength)
        :   CborBase(TypeString, TypeUndefined),
            string(pointer),
            length(stringLength)
    {}

    /*************************************************************************/
    /* Encode                                                                */
    /*************************************************************************/

    virtual uint32_t writeCBOR(uint8_t* destination, uint32_t maxLength)
    {
        uint32_t written = 0;

        if (destination)
        {
            // write tag if set
            if (tag != TypeUnassigned)
            {
                written += writeTypeAndValue(destination, maxLength, TypeTag, tag);
            }

            written += writeTypeAndValue(destination + written, maxLength - written, TypeString, length);
            written += writeBytes(destination + written, maxLength - written, (uint8_t*) string, length);
        }

        return written;
    }

    /*************************************************************************/
    /* Debug                                                                 */
    /*************************************************************************/

    virtual void print()
    {
        // write tag if set
        if (tag != TypeUnassigned)
        {
            printf("[%u] ", tag);
        }

        for (std::size_t idx = 0; idx < length; idx++)
        {
            printf("%c", string[idx]);
        }
        printf("\r\n");
    }

protected:
    const char* string;
    uint32_t length;
};


#endif // __CBOR_STRING_H__
