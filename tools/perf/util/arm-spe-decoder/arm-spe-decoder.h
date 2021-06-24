<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arm_spe_decoder.h: Arm Statistical Profiling Extensions support
 * Copyright (c) 2019-2020, Arm Ltd.
 */

#अगर_अघोषित INCLUDE__ARM_SPE_DECODER_H__
#घोषणा INCLUDE__ARM_SPE_DECODER_H__

#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>

#समावेश "arm-spe-pkt-decoder.h"

क्रमागत arm_spe_sample_type अणु
	ARM_SPE_L1D_ACCESS	= 1 << 0,
	ARM_SPE_L1D_MISS	= 1 << 1,
	ARM_SPE_LLC_ACCESS	= 1 << 2,
	ARM_SPE_LLC_MISS	= 1 << 3,
	ARM_SPE_TLB_ACCESS	= 1 << 4,
	ARM_SPE_TLB_MISS	= 1 << 5,
	ARM_SPE_BRANCH_MISS	= 1 << 6,
	ARM_SPE_REMOTE_ACCESS	= 1 << 7,
पूर्ण;

क्रमागत arm_spe_op_type अणु
	ARM_SPE_LD		= 1 << 0,
	ARM_SPE_ST		= 1 << 1,
पूर्ण;

काष्ठा arm_spe_record अणु
	क्रमागत arm_spe_sample_type type;
	पूर्णांक err;
	u32 op;
	u64 from_ip;
	u64 to_ip;
	u64 बारtamp;
	u64 virt_addr;
	u64 phys_addr;
पूर्ण;

काष्ठा arm_spe_insn;

काष्ठा arm_spe_buffer अणु
	स्थिर अचिन्हित अक्षर *buf;
	माप_प्रकार len;
	u64 offset;
	u64 trace_nr;
पूर्ण;

काष्ठा arm_spe_params अणु
	पूर्णांक (*get_trace)(काष्ठा arm_spe_buffer *buffer, व्योम *data);
	व्योम *data;
पूर्ण;

काष्ठा arm_spe_decoder अणु
	पूर्णांक (*get_trace)(काष्ठा arm_spe_buffer *buffer, व्योम *data);
	व्योम *data;
	काष्ठा arm_spe_record record;

	स्थिर अचिन्हित अक्षर *buf;
	माप_प्रकार len;

	काष्ठा arm_spe_pkt packet;
पूर्ण;

काष्ठा arm_spe_decoder *arm_spe_decoder_new(काष्ठा arm_spe_params *params);
व्योम arm_spe_decoder_मुक्त(काष्ठा arm_spe_decoder *decoder);

पूर्णांक arm_spe_decode(काष्ठा arm_spe_decoder *decoder);

#पूर्ण_अगर
