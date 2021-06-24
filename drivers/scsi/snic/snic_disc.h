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

#अगर_अघोषित __SNIC_DISC_H
#घोषणा __SNIC_DISC_H

#समावेश "snic_fwint.h"

क्रमागत snic_disc_state अणु
	SNIC_DISC_NONE,
	SNIC_DISC_INIT,
	SNIC_DISC_PENDING,
	SNIC_DISC_DONE
पूर्ण;

काष्ठा snic;
काष्ठा snic_disc अणु
	काष्ठा list_head tgt_list;
	क्रमागत snic_disc_state state;
	काष्ठा mutex mutex;
	u16	disc_id;
	u8	req_cnt;
	u32	nxt_tgt_id;
	u32	rtgt_cnt;
	u8	*rtgt_info;
	काष्ठा delayed_work disc_समयout;
	व्योम (*cb)(काष्ठा snic *);
पूर्ण;

#घोषणा SNIC_TGT_NAM_LEN	16

क्रमागत snic_tgt_state अणु
	SNIC_TGT_STAT_NONE,
	SNIC_TGT_STAT_INIT,
	SNIC_TGT_STAT_ONLINE,	/* Target is Online */
	SNIC_TGT_STAT_OFFLINE,	/* Target is Offline */
	SNIC_TGT_STAT_DEL,
पूर्ण;

काष्ठा snic_tgt_priv अणु
	काष्ठा list_head list;
	क्रमागत snic_tgt_type typ;
	u16 disc_id;
	अक्षर *name[SNIC_TGT_NAM_LEN];

	जोड़ अणु
		/*DAS Target specअगरic info */
		/*SAN Target specअगरic info */
		u8 dummmy;
	पूर्ण u;
पूर्ण;

/* snic tgt flags */
#घोषणा SNIC_TGT_SCAN_PENDING	0x01

काष्ठा snic_tgt अणु
	काष्ठा list_head list;
	u16	id;
	u16	channel;
	u32	flags;
	u32	scsi_tgt_id;
	क्रमागत snic_tgt_state state;
	काष्ठा device dev;
	काष्ठा work_काष्ठा scan_work;
	काष्ठा work_काष्ठा del_work;
	काष्ठा snic_tgt_priv tdata;
पूर्ण;


काष्ठा snic_fw_req;

व्योम snic_disc_init(काष्ठा snic_disc *);
पूर्णांक snic_disc_start(काष्ठा snic *);
व्योम snic_disc_term(काष्ठा snic *);
पूर्णांक snic_report_tgt_cmpl_handler(काष्ठा snic *, काष्ठा snic_fw_req *);
पूर्णांक snic_tgtinfo_cmpl_handler(काष्ठा snic *snic, काष्ठा snic_fw_req *fwreq);
व्योम snic_process_report_tgts_rsp(काष्ठा work_काष्ठा *);
व्योम snic_handle_tgt_disc(काष्ठा work_काष्ठा *);
व्योम snic_handle_disc(काष्ठा work_काष्ठा *);
व्योम snic_tgt_dev_release(काष्ठा device *);
व्योम snic_tgt_del_all(काष्ठा snic *);

#घोषणा dev_to_tgt(d) \
	container_of(d, काष्ठा snic_tgt, dev)

अटल अंतरभूत पूर्णांक
is_snic_target(काष्ठा device *dev)
अणु
	वापस dev->release == snic_tgt_dev_release;
पूर्ण

#घोषणा starget_to_tgt(st)	\
	(is_snic_target(((काष्ठा scsi_target *) st)->dev.parent) ? \
		dev_to_tgt(st->dev.parent) : शून्य)

#घोषणा snic_tgt_to_shost(t)	\
	dev_to_shost(t->dev.parent)

अटल अंतरभूत पूर्णांक
snic_tgt_chkपढ़ोy(काष्ठा snic_tgt *tgt)
अणु
	अगर (tgt->state == SNIC_TGT_STAT_ONLINE)
		वापस 0;
	अन्यथा
		वापस DID_NO_CONNECT << 16;
पूर्ण

स्थिर अक्षर *snic_tgt_state_to_str(पूर्णांक);
पूर्णांक snic_tgt_scsi_पात_io(काष्ठा snic_tgt *);
#पूर्ण_अगर /* end of  __SNIC_DISC_H */
