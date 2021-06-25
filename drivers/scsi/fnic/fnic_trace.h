<शैली गुरु>
/*
 * Copyright 2012 Cisco Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __FNIC_TRACE_H__
#घोषणा __FNIC_TRACE_H__

#घोषणा FNIC_ENTRY_SIZE_BYTES 64
#घोषणा FC_TRC_SIZE_BYTES 256
#घोषणा FC_TRC_HEADER_SIZE माप(काष्ठा fc_trace_hdr)

/*
 * Fisrt bit of FNIC_FC_RECV and FNIC_FC_SEND is used to represent the type
 * of frame 1 => Eth frame, 0=> FC frame
 */

#घोषणा FNIC_FC_RECV 0x52 /* Character R */
#घोषणा FNIC_FC_SEND 0x54 /* Character T */
#घोषणा FNIC_FC_LE 0x4C /* Character L */

बाह्य sमाप_प्रकार simple_पढ़ो_from_buffer(व्योम __user *to,
					  माप_प्रकार count,
					  loff_t *ppos,
					  स्थिर व्योम *from,
					  माप_प्रकार available);

बाह्य अचिन्हित पूर्णांक fnic_trace_max_pages;
बाह्य पूर्णांक fnic_tracing_enabled;
बाह्य अचिन्हित पूर्णांक trace_max_pages;

बाह्य अचिन्हित पूर्णांक fnic_fc_trace_max_pages;
बाह्य पूर्णांक fnic_fc_tracing_enabled;
बाह्य पूर्णांक fnic_fc_trace_cleared;

प्रकार काष्ठा fnic_trace_dbg अणु
	पूर्णांक wr_idx;
	पूर्णांक rd_idx;
	अचिन्हित दीर्घ *page_offset;
पूर्ण fnic_trace_dbg_t;

प्रकार काष्ठा fnic_dbgfs अणु
	पूर्णांक buffer_len;
	अक्षर *buffer;
पूर्ण fnic_dbgfs_t;

काष्ठा fnic_trace_data अणु
	जोड़ अणु
		काष्ठा अणु
			u32 low;
			u32 high;
		पूर्ण;
		u64 val;
	पूर्ण बारtamp, fnaddr;
	u32 host_no;
	u32 tag;
	u64 data[5];
पूर्ण __attribute__((__packed__));

प्रकार काष्ठा fnic_trace_data fnic_trace_data_t;

काष्ठा fc_trace_hdr अणु
	काष्ठा बारpec64 समय_stamp;
	u32 host_no;
	u8 frame_type;
	u8 frame_len;
पूर्ण __attribute__((__packed__));

#घोषणा FC_TRACE_ADDRESS(a) \
	((अचिन्हित दीर्घ)(a) + माप(काष्ठा fc_trace_hdr))

#घोषणा FNIC_TRACE_ENTRY_SIZE \
		  (FNIC_ENTRY_SIZE_BYTES - माप(fnic_trace_data_t))

#घोषणा FNIC_TRACE(_fn, _hn, _t, _a, _b, _c, _d, _e)           \
	अगर (unlikely(fnic_tracing_enabled)) अणु                   \
		fnic_trace_data_t *trace_buf = fnic_trace_get_buf(); \
		अगर (trace_buf) अणु \
			अगर (माप(अचिन्हित दीर्घ) < 8) अणु \
				trace_buf->बारtamp.low = jअगरfies; \
				trace_buf->fnaddr.low = (u32)(अचिन्हित दीर्घ)_fn; \
			पूर्ण अन्यथा अणु \
				trace_buf->बारtamp.val = jअगरfies; \
				trace_buf->fnaddr.val = (u64)(अचिन्हित दीर्घ)_fn; \
			पूर्ण \
			trace_buf->host_no = _hn; \
			trace_buf->tag = _t; \
			trace_buf->data[0] = (u64)(अचिन्हित दीर्घ)_a; \
			trace_buf->data[1] = (u64)(अचिन्हित दीर्घ)_b; \
			trace_buf->data[2] = (u64)(अचिन्हित दीर्घ)_c; \
			trace_buf->data[3] = (u64)(अचिन्हित दीर्घ)_d; \
			trace_buf->data[4] = (u64)(अचिन्हित दीर्घ)_e; \
		पूर्ण \
	पूर्ण

fnic_trace_data_t *fnic_trace_get_buf(व्योम);
पूर्णांक fnic_get_trace_data(fnic_dbgfs_t *);
पूर्णांक fnic_trace_buf_init(व्योम);
व्योम fnic_trace_मुक्त(व्योम);
पूर्णांक fnic_debugfs_init(व्योम);
व्योम fnic_debugfs_terminate(व्योम);
व्योम fnic_trace_debugfs_init(व्योम);
व्योम fnic_trace_debugfs_terminate(व्योम);

/* Fnic FC CTLR Trace releated function */
पूर्णांक fnic_fc_trace_init(व्योम);
व्योम fnic_fc_trace_मुक्त(व्योम);
पूर्णांक fnic_fc_trace_set_data(u32 host_no, u8 frame_type,
				अक्षर *frame, u32 fc_frame_len);
पूर्णांक fnic_fc_trace_get_data(fnic_dbgfs_t *fnic_dbgfs_prt, u8 rdata_flag);
व्योम copy_and_क्रमmat_trace_data(काष्ठा fc_trace_hdr *tdata,
				fnic_dbgfs_t *fnic_dbgfs_prt,
				पूर्णांक *len, u8 rdata_flag);
व्योम fnic_fc_trace_debugfs_init(व्योम);
व्योम fnic_fc_trace_debugfs_terminate(व्योम);

#पूर्ण_अगर
