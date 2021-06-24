<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
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

#अगर_अघोषित __SNIC_TRC_H
#घोषणा __SNIC_TRC_H

#अगर_घोषित CONFIG_SCSI_SNIC_DEBUG_FS

बाह्य sमाप_प्रकार simple_पढ़ो_from_buffer(व्योम __user *to,
					माप_प्रकार count,
					loff_t *ppos,
					स्थिर व्योम *from,
					माप_प्रकार available);

बाह्य अचिन्हित पूर्णांक snic_trace_max_pages;

/* Global Data काष्ठाure क्रम trace to manage trace functionality */
काष्ठा snic_trc_data अणु
	u64	ts;		/* Time Stamp */
	अक्षर	*fn;		/* Ptr to Function Name */
	u32	hno;		/* SCSI Host ID */
	u32	tag;		/* Command Tag */
	u64 data[5];
पूर्ण __attribute__((__packed__));

#घोषणा SNIC_TRC_ENTRY_SZ  64	/* in Bytes */

काष्ठा snic_trc अणु
	spinlock_t lock;
	काष्ठा snic_trc_data *buf;	/* Trace Buffer */
	u32	max_idx;		/* Max Index पूर्णांकo trace buffer */
	u32	rd_idx;
	u32	wr_idx;
	bool	enable;			/* Control Variable क्रम Tracing */

	काष्ठा dentry *trc_enable;	/* debugfs file object */
	काष्ठा dentry *trc_file;
पूर्ण;

पूर्णांक snic_trc_init(व्योम);
व्योम snic_trc_मुक्त(व्योम);
व्योम snic_trc_debugfs_init(व्योम);
व्योम snic_trc_debugfs_term(व्योम);
काष्ठा snic_trc_data *snic_get_trc_buf(व्योम);
पूर्णांक snic_get_trc_data(अक्षर *buf, पूर्णांक buf_sz);

व्योम snic_debugfs_init(व्योम);
व्योम snic_debugfs_term(व्योम);

अटल अंतरभूत व्योम
snic_trace(अक्षर *fn, u16 hno, u32 tag, u64 d1, u64 d2, u64 d3, u64 d4, u64 d5)
अणु
	काष्ठा snic_trc_data *tr_rec = snic_get_trc_buf();

	अगर (!tr_rec)
		वापस;

	tr_rec->fn = (अक्षर *)fn;
	tr_rec->hno = hno;
	tr_rec->tag = tag;
	tr_rec->data[0] = d1;
	tr_rec->data[1] = d2;
	tr_rec->data[2] = d3;
	tr_rec->data[3] = d4;
	tr_rec->data[4] = d5;
	tr_rec->ts = jअगरfies; /* Update समय stamp at last */
पूर्ण

#घोषणा SNIC_TRC(_hno, _tag, d1, d2, d3, d4, d5)			\
	करो अणु								\
		अगर (unlikely(snic_glob->trc.enable))			\
			snic_trace((अक्षर *)__func__,			\
				   (u16)(_hno),				\
				   (u32)(_tag),				\
				   (u64)(d1),				\
				   (u64)(d2),				\
				   (u64)(d3),				\
				   (u64)(d4),				\
				   (u64)(d5));				\
	पूर्ण जबतक (0)
#अन्यथा

#घोषणा SNIC_TRC(_hno, _tag, d1, d2, d3, d4, d5)	\
	करो अणु						\
		अगर (unlikely(snic_log_level & 0x2))	\
			SNIC_DBG("SnicTrace: %s %2u %2u %llx %llx %llx %llx %llx", \
				 (अक्षर *)__func__,	\
				 (u16)(_hno),		\
				 (u32)(_tag),		\
				 (u64)(d1),		\
				 (u64)(d2),		\
				 (u64)(d3),		\
				 (u64)(d4),		\
				 (u64)(d5));		\
	पूर्ण जबतक (0)
#पूर्ण_अगर /* end of CONFIG_SCSI_SNIC_DEBUG_FS */

#घोषणा SNIC_TRC_CMD(sc)	\
	((u64)sc->cmnd[0] << 56 | (u64)sc->cmnd[7] << 40 |	\
	 (u64)sc->cmnd[8] << 32 | (u64)sc->cmnd[2] << 24 |	\
	 (u64)sc->cmnd[3] << 16 | (u64)sc->cmnd[4] << 8 |	\
	 (u64)sc->cmnd[5])

#घोषणा SNIC_TRC_CMD_STATE_FLAGS(sc)	\
	((u64) CMD_FLAGS(sc) << 32 | CMD_STATE(sc))

#पूर्ण_अगर /* end of __SNIC_TRC_H */
