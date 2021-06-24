<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * V4L2 JPEG helpers header
 *
 * Copyright (C) 2019 Pengutronix, Philipp Zabel <kernel@pengutronix.de>
 *
 * For reference, see JPEG ITU-T.81 (ISO/IEC 10918-1)
 */

#अगर_अघोषित _V4L2_JPEG_H
#घोषणा _V4L2_JPEG_H

#समावेश <linux/v4l2-controls.h>

#घोषणा V4L2_JPEG_MAX_COMPONENTS	4
#घोषणा V4L2_JPEG_MAX_TABLES		4

/**
 * काष्ठा v4l2_jpeg_reference - reference पूर्णांकo the JPEG buffer
 * @start: poपूर्णांकer to the start of the referenced segment or table
 * @length: size of the referenced segment or table
 *
 * Wnen referencing marker segments, start poपूर्णांकs right after the marker code,
 * and length is the size of the segment parameters, excluding the marker code.
 */
काष्ठा v4l2_jpeg_reference अणु
	u8 *start;
	माप_प्रकार length;
पूर्ण;

/* B.2.2 Frame header syntax */

/**
 * काष्ठा v4l2_jpeg_frame_component_spec - frame component-specअगरication
 * @component_identअगरier: C[i]
 * @horizontal_sampling_factor: H[i]
 * @vertical_sampling_factor: V[i]
 * @quantization_table_selector: quantization table destination selector Tq[i]
 */
काष्ठा v4l2_jpeg_frame_component_spec अणु
	u8 component_identअगरier;
	u8 horizontal_sampling_factor;
	u8 vertical_sampling_factor;
	u8 quantization_table_selector;
पूर्ण;

/**
 * काष्ठा v4l2_jpeg_frame_header - JPEG frame header
 * @height: Y
 * @width: X
 * @precision: P
 * @num_components: Nf
 * @component: component-specअगरication, see v4l2_jpeg_frame_component_spec
 * @subsampling: decoded subsampling from component-specअगरication
 */
काष्ठा v4l2_jpeg_frame_header अणु
	u16 height;
	u16 width;
	u8 precision;
	u8 num_components;
	काष्ठा v4l2_jpeg_frame_component_spec component[V4L2_JPEG_MAX_COMPONENTS];
	क्रमागत v4l2_jpeg_chroma_subsampling subsampling;
पूर्ण;

/* B.2.3 Scan header syntax */

/**
 * काष्ठा v4l2_jpeg_scan_component_spec - scan component-specअगरication
 * @component_selector: Cs[j]
 * @dc_entropy_coding_table_selector: Td[j]
 * @ac_entropy_coding_table_selector: Ta[j]
 */
काष्ठा v4l2_jpeg_scan_component_spec अणु
	u8 component_selector;
	u8 dc_entropy_coding_table_selector;
	u8 ac_entropy_coding_table_selector;
पूर्ण;

/**
 * काष्ठा v4l2_jpeg_scan_header - JPEG scan header
 * @num_components: Ns
 * @component: component-specअगरication, see v4l2_jpeg_scan_component_spec
 */
काष्ठा v4l2_jpeg_scan_header अणु
	u8 num_components;				/* Ns */
	काष्ठा v4l2_jpeg_scan_component_spec component[V4L2_JPEG_MAX_COMPONENTS];
	/* Ss, Se, Ah, and Al are not used by any driver */
पूर्ण;

/**
 * क्रमागत v4l2_jpeg_app14_tf - APP14 transक्रमm flag
 * According to Rec. ITU-T T.872 (06/2012) 6.5.3
 * APP14 segment is क्रम color encoding, it contains a transक्रमm flag,
 * which may have values of 0, 1 and 2 and are पूर्णांकerpreted as follows:
 * @V4L2_JPEG_APP14_TF_CMYK_RGB: CMYK क्रम images encoded with four components
 *                               RGB क्रम images encoded with three components
 * @V4L2_JPEG_APP14_TF_YCBCR: an image encoded with three components using YCbCr
 * @V4L2_JPEG_APP14_TF_YCCK: an image encoded with four components using YCCK
 * @V4L2_JPEG_APP14_TF_UNKNOWN: indicate app14 is not present
 */
क्रमागत v4l2_jpeg_app14_tf अणु
	V4L2_JPEG_APP14_TF_CMYK_RGB	= 0,
	V4L2_JPEG_APP14_TF_YCBCR	= 1,
	V4L2_JPEG_APP14_TF_YCCK		= 2,
	V4L2_JPEG_APP14_TF_UNKNOWN	= -1,
पूर्ण;

/**
 * काष्ठा v4l2_jpeg_header - parsed JPEG header
 * @sof: poपूर्णांकer to frame header and size
 * @sos: poपूर्णांकer to scan header and size
 * @num_dht: number of entries in @dht
 * @dht: poपूर्णांकers to huffman tables and sizes
 * @num_dqt: number of entries in @dqt
 * @dqt: poपूर्णांकers to quantization tables and sizes
 * @frame: parsed frame header
 * @scan: poपूर्णांकer to parsed scan header, optional
 * @quantization_tables: references to four quantization tables, optional
 * @huffman_tables: references to four Huffman tables in DC0, DC1, AC0, AC1
 *                  order, optional
 * @restart_पूर्णांकerval: number of MCU per restart पूर्णांकerval, Ri
 * @ecs_offset: buffer offset in bytes to the entropy coded segment
 * @app14_tf: transक्रमm flag from app14 data
 *
 * When this काष्ठाure is passed to v4l2_jpeg_parse_header, the optional scan,
 * quantization_tables, and huffman_tables poपूर्णांकers must be initialized to शून्य
 * or poपूर्णांक at valid memory.
 */
काष्ठा v4l2_jpeg_header अणु
	काष्ठा v4l2_jpeg_reference sof;
	काष्ठा v4l2_jpeg_reference sos;
	अचिन्हित पूर्णांक num_dht;
	काष्ठा v4l2_jpeg_reference dht[V4L2_JPEG_MAX_TABLES];
	अचिन्हित पूर्णांक num_dqt;
	काष्ठा v4l2_jpeg_reference dqt[V4L2_JPEG_MAX_TABLES];

	काष्ठा v4l2_jpeg_frame_header frame;
	काष्ठा v4l2_jpeg_scan_header *scan;
	काष्ठा v4l2_jpeg_reference *quantization_tables;
	काष्ठा v4l2_jpeg_reference *huffman_tables;
	u16 restart_पूर्णांकerval;
	माप_प्रकार ecs_offset;
	क्रमागत v4l2_jpeg_app14_tf app14_tf;
पूर्ण;

पूर्णांक v4l2_jpeg_parse_header(व्योम *buf, माप_प्रकार len, काष्ठा v4l2_jpeg_header *out);

पूर्णांक v4l2_jpeg_parse_frame_header(व्योम *buf, माप_प्रकार len,
				 काष्ठा v4l2_jpeg_frame_header *frame_header);
पूर्णांक v4l2_jpeg_parse_scan_header(व्योम *buf, माप_प्रकार len,
				काष्ठा v4l2_jpeg_scan_header *scan_header);
पूर्णांक v4l2_jpeg_parse_quantization_tables(व्योम *buf, माप_प्रकार len, u8 precision,
					काष्ठा v4l2_jpeg_reference *q_tables);
पूर्णांक v4l2_jpeg_parse_huffman_tables(व्योम *buf, माप_प्रकार len,
				   काष्ठा v4l2_jpeg_reference *huffman_tables);

#पूर्ण_अगर
