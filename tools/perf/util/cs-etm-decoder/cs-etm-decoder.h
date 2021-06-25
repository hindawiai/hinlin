<शैली गुरु>
/*
 * SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright(C) 2015-2018 Linaro Limited.
 *
 * Author: Tor Jeremiassen <tor@ti.com>
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#अगर_अघोषित INCLUDE__CS_ETM_DECODER_H__
#घोषणा INCLUDE__CS_ETM_DECODER_H__

#समावेश <linux/types.h>
#समावेश <मानकपन.स>

काष्ठा cs_eपंचांग_decoder;
काष्ठा cs_eपंचांग_packet;
काष्ठा cs_eपंचांग_packet_queue;

काष्ठा cs_eपंचांग_queue;

प्रकार u32 (*cs_eपंचांग_mem_cb_type)(काष्ठा cs_eपंचांग_queue *, u8, u64, माप_प्रकार, u8 *);

काष्ठा cs_eपंचांगv3_trace_params अणु
	u32 reg_ctrl;
	u32 reg_trc_id;
	u32 reg_ccer;
	u32 reg_idr;
पूर्ण;

काष्ठा cs_eपंचांगv4_trace_params अणु
	u32 reg_idr0;
	u32 reg_idr1;
	u32 reg_idr2;
	u32 reg_idr8;
	u32 reg_configr;
	u32 reg_traceidr;
पूर्ण;

काष्ठा cs_eपंचांग_trace_params अणु
	पूर्णांक protocol;
	जोड़ अणु
		काष्ठा cs_eपंचांगv3_trace_params eपंचांगv3;
		काष्ठा cs_eपंचांगv4_trace_params eपंचांगv4;
	पूर्ण;
पूर्ण;

काष्ठा cs_eपंचांग_decoder_params अणु
	पूर्णांक operation;
	व्योम (*packet_prपूर्णांकer)(स्थिर अक्षर *msg);
	cs_eपंचांग_mem_cb_type mem_acc_cb;
	u8 क्रमmatted;
	u8 fsyncs;
	u8 hsyncs;
	u8 frame_aligned;
	व्योम *data;
पूर्ण;

/*
 * The following क्रमागतs are indexed starting with 1 to align with the
 * खोलो source coresight trace decoder library.
 */
क्रमागत अणु
	CS_ETM_PROTO_ETMV3 = 1,
	CS_ETM_PROTO_ETMV4i,
	CS_ETM_PROTO_ETMV4d,
	CS_ETM_PROTO_PTM,
पूर्ण;

क्रमागत cs_eपंचांग_decoder_operation अणु
	CS_ETM_OPERATION_PRINT = 1,
	CS_ETM_OPERATION_DECODE,
	CS_ETM_OPERATION_MAX,
पूर्ण;

पूर्णांक cs_eपंचांग_decoder__process_data_block(काष्ठा cs_eपंचांग_decoder *decoder,
				       u64 indx, स्थिर u8 *buf,
				       माप_प्रकार len, माप_प्रकार *consumed);

काष्ठा cs_eपंचांग_decoder *
cs_eपंचांग_decoder__new(पूर्णांक num_cpu,
		    काष्ठा cs_eपंचांग_decoder_params *d_params,
		    काष्ठा cs_eपंचांग_trace_params t_params[]);

व्योम cs_eपंचांग_decoder__मुक्त(काष्ठा cs_eपंचांग_decoder *decoder);

पूर्णांक cs_eपंचांग_decoder__add_mem_access_cb(काष्ठा cs_eपंचांग_decoder *decoder,
				      u64 start, u64 end,
				      cs_eपंचांग_mem_cb_type cb_func);

पूर्णांक cs_eपंचांग_decoder__get_packet(काष्ठा cs_eपंचांग_packet_queue *packet_queue,
			       काष्ठा cs_eपंचांग_packet *packet);

पूर्णांक cs_eपंचांग_decoder__reset(काष्ठा cs_eपंचांग_decoder *decoder);

#पूर्ण_अगर /* INCLUDE__CS_ETM_DECODER_H__ */
