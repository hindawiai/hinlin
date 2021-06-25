<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#घोषणा REQUEST(r_contents) \
	REQUEST_(REQUEST_NAME, REQUEST_NUM, REQUEST_IDX_KIND, I(r_contents))

#घोषणा __field(f_offset, f_bytes, f_name) \
	__field_(REQUEST_NAME, REQUEST_NUM, REQUEST_IDX_KIND, \
		 f_offset, f_bytes, f_name)

#घोषणा __array(f_offset, f_bytes, f_name) \
	__array_(REQUEST_NAME, REQUEST_NUM, REQUEST_IDX_KIND, \
		 f_offset, f_bytes, f_name)

#घोषणा __count(f_offset, f_bytes, f_name) \
	__count_(REQUEST_NAME, REQUEST_NUM, REQUEST_IDX_KIND, \
		 f_offset, f_bytes, f_name)
