<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tools/testing/selftests/kvm/include/sparsebit.h
 *
 * Copyright (C) 2018, Google LLC.
 *
 * Header file that describes API to the sparsebit library.
 * This library provides a memory efficient means of storing
 * the settings of bits indexed via a uपूर्णांक64_t.  Memory usage
 * is reasonable, signअगरicantly less than (2^64 / 8) bytes, as
 * दीर्घ as bits that are mostly set or mostly cleared are बंद
 * to each other.  This library is efficient in memory usage
 * even in the हाल where most bits are set.
 */

#अगर_अघोषित SELFTEST_KVM_SPARSEBIT_H
#घोषणा SELFTEST_KVM_SPARSEBIT_H

#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

काष्ठा sparsebit;
प्रकार uपूर्णांक64_t sparsebit_idx_t;
प्रकार uपूर्णांक64_t sparsebit_num_t;

काष्ठा sparsebit *sparsebit_alloc(व्योम);
व्योम sparsebit_मुक्त(काष्ठा sparsebit **sbitp);
व्योम sparsebit_copy(काष्ठा sparsebit *dstp, काष्ठा sparsebit *src);

bool sparsebit_is_set(काष्ठा sparsebit *sbit, sparsebit_idx_t idx);
bool sparsebit_is_set_num(काष्ठा sparsebit *sbit,
			  sparsebit_idx_t idx, sparsebit_num_t num);
bool sparsebit_is_clear(काष्ठा sparsebit *sbit, sparsebit_idx_t idx);
bool sparsebit_is_clear_num(काष्ठा sparsebit *sbit,
			    sparsebit_idx_t idx, sparsebit_num_t num);
sparsebit_num_t sparsebit_num_set(काष्ठा sparsebit *sbit);
bool sparsebit_any_set(काष्ठा sparsebit *sbit);
bool sparsebit_any_clear(काष्ठा sparsebit *sbit);
bool sparsebit_all_set(काष्ठा sparsebit *sbit);
bool sparsebit_all_clear(काष्ठा sparsebit *sbit);
sparsebit_idx_t sparsebit_first_set(काष्ठा sparsebit *sbit);
sparsebit_idx_t sparsebit_first_clear(काष्ठा sparsebit *sbit);
sparsebit_idx_t sparsebit_next_set(काष्ठा sparsebit *sbit, sparsebit_idx_t prev);
sparsebit_idx_t sparsebit_next_clear(काष्ठा sparsebit *sbit, sparsebit_idx_t prev);
sparsebit_idx_t sparsebit_next_set_num(काष्ठा sparsebit *sbit,
				       sparsebit_idx_t start, sparsebit_num_t num);
sparsebit_idx_t sparsebit_next_clear_num(काष्ठा sparsebit *sbit,
					 sparsebit_idx_t start, sparsebit_num_t num);

व्योम sparsebit_set(काष्ठा sparsebit *sbitp, sparsebit_idx_t idx);
व्योम sparsebit_set_num(काष्ठा sparsebit *sbitp, sparsebit_idx_t start,
		       sparsebit_num_t num);
व्योम sparsebit_set_all(काष्ठा sparsebit *sbitp);

व्योम sparsebit_clear(काष्ठा sparsebit *sbitp, sparsebit_idx_t idx);
व्योम sparsebit_clear_num(काष्ठा sparsebit *sbitp,
			 sparsebit_idx_t start, sparsebit_num_t num);
व्योम sparsebit_clear_all(काष्ठा sparsebit *sbitp);

व्योम sparsebit_dump(खाता *stream, काष्ठा sparsebit *sbit,
		    अचिन्हित पूर्णांक indent);
व्योम sparsebit_validate_पूर्णांकernal(काष्ठा sparsebit *sbit);

#अगर_घोषित __cplusplus
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* SELFTEST_KVM_SPARSEBIT_H */
