<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __IA_CSS_ISYS_H__
#घोषणा __IA_CSS_ISYS_H__

#समावेश <type_support.h>
#समावेश <input_प्रणाली.h>
#समावेश <ia_css_input_port.h>
#समावेश <ia_css_stream_क्रमmat.h>
#समावेश <ia_css_stream_खुला.h>
#समावेश <प्रणाली_global.h>
#समावेश "ia_css_isys_comm.h"

#अगर_घोषित ISP2401
/**
 * Virtual Input System. (Input System 2401)
 */
प्रकार isp2401_input_प्रणाली_cfg_t	ia_css_isys_descr_t;
/* end of Virtual Input System */
#पूर्ण_अगर

input_प्रणाली_err_t ia_css_isys_init(व्योम);
व्योम ia_css_isys_uninit(व्योम);
क्रमागत mipi_port_id ia_css_isys_port_to_mipi_port(
    क्रमागत mipi_port_id api_port);

#अगर defined(ISP2401)

/**
 * @brief Register one (भव) stream. This is used to track when all
 * भव streams are configured inside the input प्रणाली. The CSI RX is
 * only started when all रेजिस्टरed streams are configured.
 *
 * @param[in]	port		CSI port
 * @param[in]	isys_stream_id	Stream handle generated with ia_css_isys_generate_stream_id()
 *				Must be lower than SH_CSS_MAX_ISYS_CHANNEL_NODES
 * @वापस			0 अगर successful, -EINVAL अगर
 *				there is alपढ़ोy a stream रेजिस्टरed with the same handle
 */
पूर्णांक ia_css_isys_csi_rx_रेजिस्टर_stream(
    क्रमागत mipi_port_id port,
    uपूर्णांक32_t isys_stream_id);

/**
 * @brief Unरेजिस्टर one (भव) stream. This is used to track when all
 * भव streams are configured inside the input प्रणाली. The CSI RX is
 * only started when all रेजिस्टरed streams are configured.
 *
 * @param[in]	port		CSI port
 * @param[in]	isys_stream_id	Stream handle generated with ia_css_isys_generate_stream_id()
 *				Must be lower than SH_CSS_MAX_ISYS_CHANNEL_NODES
 * @वापस			0 अगर successful, -EINVAL अगर
 *				there is no stream रेजिस्टरed with that handle
 */
पूर्णांक ia_css_isys_csi_rx_unरेजिस्टर_stream(
    क्रमागत mipi_port_id port,
    uपूर्णांक32_t isys_stream_id);

पूर्णांक ia_css_isys_convert_compressed_क्रमmat(
    काष्ठा ia_css_csi2_compression *comp,
    काष्ठा isp2401_input_प्रणाली_cfg_s *cfg);
अचिन्हित पूर्णांक ia_css_csi2_calculate_input_प्रणाली_alignment(
    क्रमागत atomisp_input_क्रमmat fmt_type);
#पूर्ण_अगर

#अगर !defined(ISP2401)
/* CSS Receiver */
व्योम ia_css_isys_rx_configure(
    स्थिर rx_cfg_t *config,
    स्थिर क्रमागत ia_css_input_mode input_mode);

व्योम ia_css_isys_rx_disable(व्योम);

व्योम ia_css_isys_rx_enable_all_पूर्णांकerrupts(क्रमागत mipi_port_id port);

अचिन्हित पूर्णांक ia_css_isys_rx_get_पूर्णांकerrupt_reg(क्रमागत mipi_port_id port);
व्योम ia_css_isys_rx_get_irq_info(क्रमागत mipi_port_id port,
				 अचिन्हित पूर्णांक *irq_infos);
व्योम ia_css_isys_rx_clear_irq_info(क्रमागत mipi_port_id port,
				   अचिन्हित पूर्णांक irq_infos);
अचिन्हित पूर्णांक ia_css_isys_rx_translate_irq_infos(अचिन्हित पूर्णांक bits);

#पूर्ण_अगर /* #अगर !defined(ISP2401) */

/* @brief Translate क्रमmat and compression to क्रमmat type.
 *
 * @param[in]	input_क्रमmat	The input क्रमmat.
 * @param[in]	compression	The compression scheme.
 * @param[out]	fmt_type	Poपूर्णांकer to the resulting क्रमmat type.
 * @वापस			Error code.
 *
 * Translate an input क्रमmat and mipi compression pair to the fmt_type.
 * This is normally करोne by the sensor, but when using the input fअगरo, this
 * क्रमmat type must be sumitted correctly by the application.
 */
पूर्णांक ia_css_isys_convert_stream_क्रमmat_to_mipi_क्रमmat(
    क्रमागत atomisp_input_क्रमmat input_क्रमmat,
    mipi_predictor_t compression,
    अचिन्हित पूर्णांक *fmt_type);

#अगर_घोषित ISP2401
/**
 * Virtual Input System. (Input System 2401)
 */
ia_css_isys_error_t ia_css_isys_stream_create(
    ia_css_isys_descr_t	*isys_stream_descr,
    ia_css_isys_stream_h	isys_stream,
    uपूर्णांक32_t isys_stream_id);

व्योम ia_css_isys_stream_destroy(
    ia_css_isys_stream_h	isys_stream);

ia_css_isys_error_t ia_css_isys_stream_calculate_cfg(
    ia_css_isys_stream_h		isys_stream,
    ia_css_isys_descr_t		*isys_stream_descr,
    ia_css_isys_stream_cfg_t	*isys_stream_cfg);

व्योम ia_css_isys_csi_rx_lut_rmgr_init(व्योम);

व्योम ia_css_isys_csi_rx_lut_rmgr_uninit(व्योम);

bool ia_css_isys_csi_rx_lut_rmgr_acquire(
    csi_rx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_rx_backend_lut_entry_t	*entry);

व्योम ia_css_isys_csi_rx_lut_rmgr_release(
    csi_rx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_rx_backend_lut_entry_t	*entry);

व्योम ia_css_isys_ibuf_rmgr_init(व्योम);

व्योम ia_css_isys_ibuf_rmgr_uninit(व्योम);

bool ia_css_isys_ibuf_rmgr_acquire(
    u32	size,
    uपूर्णांक32_t	*start_addr);

व्योम ia_css_isys_ibuf_rmgr_release(
    uपूर्णांक32_t	*start_addr);

व्योम ia_css_isys_dma_channel_rmgr_init(व्योम);

व्योम ia_css_isys_dma_channel_rmgr_uninit(व्योम);

bool ia_css_isys_dma_channel_rmgr_acquire(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channel	*channel);

व्योम ia_css_isys_dma_channel_rmgr_release(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channel	*channel);

व्योम ia_css_isys_stream2mmio_sid_rmgr_init(व्योम);

व्योम ia_css_isys_stream2mmio_sid_rmgr_uninit(व्योम);

bool ia_css_isys_stream2mmio_sid_rmgr_acquire(
    stream2mmio_ID_t	stream2mmio,
    stream2mmio_sid_ID_t	*sid);

व्योम ia_css_isys_stream2mmio_sid_rmgr_release(
    stream2mmio_ID_t	stream2mmio,
    stream2mmio_sid_ID_t	*sid);

/* end of Virtual Input System */
#पूर्ण_अगर

#पूर्ण_अगर				/* __IA_CSS_ISYS_H__ */
