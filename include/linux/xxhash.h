<शैली गुरु>
/*
 * xxHash - Extremely Fast Hash algorithm
 * Copyright (C) 2012-2016, Yann Collet.
 *
 * BSD 2-Clause License (http://www.खोलोsource.org/licenses/bsd-license.php)
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above
 *     copyright notice, this list of conditions and the following disclaimer
 *     in the करोcumentation and/or other materials provided with the
 *     distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it under
 * the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation. This program is dual-licensed; you may select
 * either version 2 of the GNU General Public License ("GPL") or BSD license
 * ("BSD").
 *
 * You can contact the author at:
 * - xxHash homepage: https://cyan4973.github.io/xxHash/
 * - xxHash source repository: https://github.com/Cyan4973/xxHash
 */

/*
 * Notice extracted from xxHash homepage:
 *
 * xxHash is an extremely fast Hash algorithm, running at RAM speed limits.
 * It also successfully passes all tests from the SMHasher suite.
 *
 * Comparison (single thपढ़ो, Winकरोws Seven 32 bits, using SMHasher on a Core 2
 * Duo @3GHz)
 *
 * Name            Speed       Q.Score   Author
 * xxHash          5.4 GB/s     10
 * CrapWow         3.2 GB/s      2       Andrew
 * MumurHash 3a    2.7 GB/s     10       Austin Appleby
 * SpookyHash      2.0 GB/s     10       Bob Jenkins
 * SBox            1.4 GB/s      9       Bret Mulvey
 * Lookup3         1.2 GB/s      9       Bob Jenkins
 * SuperFastHash   1.2 GB/s      1       Paul Hsieh
 * CityHash64      1.05 GB/s    10       Pike & Alakuijala
 * FNV             0.55 GB/s     5       Fowler, Noll, Vo
 * CRC32           0.43 GB/s     9
 * MD5-32          0.33 GB/s    10       Ronald L. Rivest
 * SHA1-32         0.28 GB/s    10
 *
 * Q.Score is a measure of quality of the hash function.
 * It depends on successfully passing SMHasher test set.
 * 10 is a perfect score.
 *
 * A 64-bits version, named xxh64 offers much better speed,
 * but क्रम 64-bits applications only.
 * Name     Speed on 64 bits    Speed on 32 bits
 * xxh64       13.8 GB/s            1.9 GB/s
 * xxh32        6.8 GB/s            6.0 GB/s
 */

#अगर_अघोषित XXHASH_H
#घोषणा XXHASH_H

#समावेश <linux/types.h>

/*-****************************
 * Simple Hash Functions
 *****************************/

/**
 * xxh32() - calculate the 32-bit hash of the input with a given seed.
 *
 * @input:  The data to hash.
 * @length: The length of the data to hash.
 * @seed:   The seed can be used to alter the result predictably.
 *
 * Speed on Core 2 Duo @ 3 GHz (single thपढ़ो, SMHasher benchmark) : 5.4 GB/s
 *
 * Return:  The 32-bit hash of the data.
 */
uपूर्णांक32_t xxh32(स्थिर व्योम *input, माप_प्रकार length, uपूर्णांक32_t seed);

/**
 * xxh64() - calculate the 64-bit hash of the input with a given seed.
 *
 * @input:  The data to hash.
 * @length: The length of the data to hash.
 * @seed:   The seed can be used to alter the result predictably.
 *
 * This function runs 2x faster on 64-bit प्रणालीs, but slower on 32-bit प्रणालीs.
 *
 * Return:  The 64-bit hash of the data.
 */
uपूर्णांक64_t xxh64(स्थिर व्योम *input, माप_प्रकार length, uपूर्णांक64_t seed);

/**
 * xxhash() - calculate wordsize hash of the input with a given seed
 * @input:  The data to hash.
 * @length: The length of the data to hash.
 * @seed:   The seed can be used to alter the result predictably.
 *
 * If the hash करोes not need to be comparable between machines with
 * dअगरferent word sizes, this function will call whichever of xxh32()
 * or xxh64() is faster.
 *
 * Return:  wordsize hash of the data.
 */

अटल अंतरभूत अचिन्हित दीर्घ xxhash(स्थिर व्योम *input, माप_प्रकार length,
				   uपूर्णांक64_t seed)
अणु
#अगर BITS_PER_LONG == 64
       वापस xxh64(input, length, seed);
#अन्यथा
       वापस xxh32(input, length, seed);
#पूर्ण_अगर
पूर्ण

/*-****************************
 * Streaming Hash Functions
 *****************************/

/*
 * These definitions are only meant to allow allocation of XXH state
 * अटलally, on stack, or in a काष्ठा क्रम example.
 * Do not use members directly.
 */

/**
 * काष्ठा xxh32_state - निजी xxh32 state, करो not use members directly
 */
काष्ठा xxh32_state अणु
	uपूर्णांक32_t total_len_32;
	uपूर्णांक32_t large_len;
	uपूर्णांक32_t v1;
	uपूर्णांक32_t v2;
	uपूर्णांक32_t v3;
	uपूर्णांक32_t v4;
	uपूर्णांक32_t mem32[4];
	uपूर्णांक32_t memsize;
पूर्ण;

/**
 * काष्ठा xxh32_state - निजी xxh64 state, करो not use members directly
 */
काष्ठा xxh64_state अणु
	uपूर्णांक64_t total_len;
	uपूर्णांक64_t v1;
	uपूर्णांक64_t v2;
	uपूर्णांक64_t v3;
	uपूर्णांक64_t v4;
	uपूर्णांक64_t mem64[4];
	uपूर्णांक32_t memsize;
पूर्ण;

/**
 * xxh32_reset() - reset the xxh32 state to start a new hashing operation
 *
 * @state: The xxh32 state to reset.
 * @seed:  Initialize the hash state with this seed.
 *
 * Call this function on any xxh32_state to prepare क्रम a new hashing operation.
 */
व्योम xxh32_reset(काष्ठा xxh32_state *state, uपूर्णांक32_t seed);

/**
 * xxh32_update() - hash the data given and update the xxh32 state
 *
 * @state:  The xxh32 state to update.
 * @input:  The data to hash.
 * @length: The length of the data to hash.
 *
 * After calling xxh32_reset() call xxh32_update() as many बार as necessary.
 *
 * Return:  Zero on success, otherwise an error code.
 */
पूर्णांक xxh32_update(काष्ठा xxh32_state *state, स्थिर व्योम *input, माप_प्रकार length);

/**
 * xxh32_digest() - produce the current xxh32 hash
 *
 * @state: Produce the current xxh32 hash of this state.
 *
 * A hash value can be produced at any समय. It is still possible to जारी
 * inserting input पूर्णांकo the hash state after a call to xxh32_digest(), and
 * generate new hashes later on, by calling xxh32_digest() again.
 *
 * Return: The xxh32 hash stored in the state.
 */
uपूर्णांक32_t xxh32_digest(स्थिर काष्ठा xxh32_state *state);

/**
 * xxh64_reset() - reset the xxh64 state to start a new hashing operation
 *
 * @state: The xxh64 state to reset.
 * @seed:  Initialize the hash state with this seed.
 */
व्योम xxh64_reset(काष्ठा xxh64_state *state, uपूर्णांक64_t seed);

/**
 * xxh64_update() - hash the data given and update the xxh64 state
 * @state:  The xxh64 state to update.
 * @input:  The data to hash.
 * @length: The length of the data to hash.
 *
 * After calling xxh64_reset() call xxh64_update() as many बार as necessary.
 *
 * Return:  Zero on success, otherwise an error code.
 */
पूर्णांक xxh64_update(काष्ठा xxh64_state *state, स्थिर व्योम *input, माप_प्रकार length);

/**
 * xxh64_digest() - produce the current xxh64 hash
 *
 * @state: Produce the current xxh64 hash of this state.
 *
 * A hash value can be produced at any समय. It is still possible to जारी
 * inserting input पूर्णांकo the hash state after a call to xxh64_digest(), and
 * generate new hashes later on, by calling xxh64_digest() again.
 *
 * Return: The xxh64 hash stored in the state.
 */
uपूर्णांक64_t xxh64_digest(स्थिर काष्ठा xxh64_state *state);

/*-**************************
 * Utils
 ***************************/

/**
 * xxh32_copy_state() - copy the source state पूर्णांकo the destination state
 *
 * @src: The source xxh32 state.
 * @dst: The destination xxh32 state.
 */
व्योम xxh32_copy_state(काष्ठा xxh32_state *dst, स्थिर काष्ठा xxh32_state *src);

/**
 * xxh64_copy_state() - copy the source state पूर्णांकo the destination state
 *
 * @src: The source xxh64 state.
 * @dst: The destination xxh64 state.
 */
व्योम xxh64_copy_state(काष्ठा xxh64_state *dst, स्थिर काष्ठा xxh64_state *src);

#पूर्ण_अगर /* XXHASH_H */
