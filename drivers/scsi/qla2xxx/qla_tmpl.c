<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"
#समावेश "qla_tmpl.h"

#घोषणा ISPREG(vha)	(&(vha)->hw->iobase->isp24)
#घोषणा IOBAR(reg)	दुरत्व(typeof(*(reg)), iobase_addr)
#घोषणा IOBASE(vha)	IOBAR(ISPREG(vha))
#घोषणा INVALID_ENTRY ((काष्ठा qla27xx_fwdt_entry *)0xffffffffffffffffUL)

अटल अंतरभूत व्योम
qla27xx_insert16(uपूर्णांक16_t value, व्योम *buf, uदीर्घ *len)
अणु
	अगर (buf) अणु
		buf += *len;
		*(__le16 *)buf = cpu_to_le16(value);
	पूर्ण
	*len += माप(value);
पूर्ण

अटल अंतरभूत व्योम
qla27xx_insert32(uपूर्णांक32_t value, व्योम *buf, uदीर्घ *len)
अणु
	अगर (buf) अणु
		buf += *len;
		*(__le32 *)buf = cpu_to_le32(value);
	पूर्ण
	*len += माप(value);
पूर्ण

अटल अंतरभूत व्योम
qla27xx_insertbuf(व्योम *mem, uदीर्घ size, व्योम *buf, uदीर्घ *len)
अणु
	अगर (buf && mem && size) अणु
		buf += *len;
		स_नकल(buf, mem, size);
	पूर्ण
	*len += size;
पूर्ण

अटल अंतरभूत व्योम
qla27xx_पढ़ो8(व्योम __iomem *winकरोw, व्योम *buf, uदीर्घ *len)
अणु
	uपूर्णांक8_t value = ~0;

	अगर (buf) अणु
		value = rd_reg_byte(winकरोw);
	पूर्ण
	qla27xx_insert32(value, buf, len);
पूर्ण

अटल अंतरभूत व्योम
qla27xx_पढ़ो16(व्योम __iomem *winकरोw, व्योम *buf, uदीर्घ *len)
अणु
	uपूर्णांक16_t value = ~0;

	अगर (buf) अणु
		value = rd_reg_word(winकरोw);
	पूर्ण
	qla27xx_insert32(value, buf, len);
पूर्ण

अटल अंतरभूत व्योम
qla27xx_पढ़ो32(व्योम __iomem *winकरोw, व्योम *buf, uदीर्घ *len)
अणु
	uपूर्णांक32_t value = ~0;

	अगर (buf) अणु
		value = rd_reg_dword(winकरोw);
	पूर्ण
	qla27xx_insert32(value, buf, len);
पूर्ण

अटल अंतरभूत व्योम (*qla27xx_पढ़ो_vector(uपूर्णांक width))(व्योम __iomem*, व्योम *, uदीर्घ *)
अणु
	वापस
	    (width == 1) ? qla27xx_पढ़ो8 :
	    (width == 2) ? qla27xx_पढ़ो16 :
			   qla27xx_पढ़ो32;
पूर्ण

अटल अंतरभूत व्योम
qla27xx_पढ़ो_reg(__iomem काष्ठा device_reg_24xx *reg,
	uपूर्णांक offset, व्योम *buf, uदीर्घ *len)
अणु
	व्योम __iomem *winकरोw = (व्योम __iomem *)reg + offset;

	qla27xx_पढ़ो32(winकरोw, buf, len);
पूर्ण

अटल अंतरभूत व्योम
qla27xx_ग_लिखो_reg(__iomem काष्ठा device_reg_24xx *reg,
	uपूर्णांक offset, uपूर्णांक32_t data, व्योम *buf)
अणु
	अगर (buf) अणु
		व्योम __iomem *winकरोw = (व्योम __iomem *)reg + offset;

		wrt_reg_dword(winकरोw, data);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
qla27xx_पढ़ो_winकरोw(__iomem काष्ठा device_reg_24xx *reg,
	uपूर्णांक32_t addr, uपूर्णांक offset, uपूर्णांक count, uपूर्णांक width, व्योम *buf,
	uदीर्घ *len)
अणु
	व्योम __iomem *winकरोw = (व्योम __iomem *)reg + offset;
	व्योम (*पढ़ोn)(व्योम __iomem*, व्योम *, uदीर्घ *) = qla27xx_पढ़ो_vector(width);

	qla27xx_ग_लिखो_reg(reg, IOBAR(reg), addr, buf);
	जबतक (count--) अणु
		qla27xx_insert32(addr, buf, len);
		पढ़ोn(winकरोw, buf, len);
		winकरोw += width;
		addr++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
qla27xx_skip_entry(काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf)
अणु
	अगर (buf)
		ent->hdr.driver_flags |= DRIVER_FLAG_SKIP_ENTRY;
पूर्ण

अटल अंतरभूत काष्ठा qla27xx_fwdt_entry *
qla27xx_next_entry(काष्ठा qla27xx_fwdt_entry *ent)
अणु
	वापस (व्योम *)ent + le32_to_cpu(ent->hdr.size);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t0(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	ql_dbg(ql_dbg_misc, vha, 0xd100,
	    "%s: nop [%lx]\n", __func__, *len);
	qla27xx_skip_entry(ent, buf);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t255(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	ql_dbg(ql_dbg_misc, vha, 0xd1ff,
	    "%s: end [%lx]\n", __func__, *len);
	qla27xx_skip_entry(ent, buf);

	/* terminate */
	वापस शून्य;
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t256(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ addr = le32_to_cpu(ent->t256.base_addr);
	uपूर्णांक offset = ent->t256.pci_offset;
	uदीर्घ count = le16_to_cpu(ent->t256.reg_count);
	uपूर्णांक width = ent->t256.reg_width;

	ql_dbg(ql_dbg_misc, vha, 0xd200,
	    "%s: rdio t1 [%lx]\n", __func__, *len);
	qla27xx_पढ़ो_winकरोw(ISPREG(vha), addr, offset, count, width, buf, len);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t257(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ addr = le32_to_cpu(ent->t257.base_addr);
	uपूर्णांक offset = ent->t257.pci_offset;
	uदीर्घ data = le32_to_cpu(ent->t257.ग_लिखो_data);

	ql_dbg(ql_dbg_misc, vha, 0xd201,
	    "%s: wrio t1 [%lx]\n", __func__, *len);
	qla27xx_ग_लिखो_reg(ISPREG(vha), IOBASE(vha), addr, buf);
	qla27xx_ग_लिखो_reg(ISPREG(vha), offset, data, buf);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t258(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uपूर्णांक banksel = ent->t258.banksel_offset;
	uदीर्घ bank = le32_to_cpu(ent->t258.bank);
	uदीर्घ addr = le32_to_cpu(ent->t258.base_addr);
	uपूर्णांक offset = ent->t258.pci_offset;
	uपूर्णांक count = le16_to_cpu(ent->t258.reg_count);
	uपूर्णांक width = ent->t258.reg_width;

	ql_dbg(ql_dbg_misc, vha, 0xd202,
	    "%s: rdio t2 [%lx]\n", __func__, *len);
	qla27xx_ग_लिखो_reg(ISPREG(vha), banksel, bank, buf);
	qla27xx_पढ़ो_winकरोw(ISPREG(vha), addr, offset, count, width, buf, len);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t259(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ addr = le32_to_cpu(ent->t259.base_addr);
	uपूर्णांक banksel = ent->t259.banksel_offset;
	uदीर्घ bank = le32_to_cpu(ent->t259.bank);
	uपूर्णांक offset = ent->t259.pci_offset;
	uदीर्घ data = le32_to_cpu(ent->t259.ग_लिखो_data);

	ql_dbg(ql_dbg_misc, vha, 0xd203,
	    "%s: wrio t2 [%lx]\n", __func__, *len);
	qla27xx_ग_लिखो_reg(ISPREG(vha), IOBASE(vha), addr, buf);
	qla27xx_ग_लिखो_reg(ISPREG(vha), banksel, bank, buf);
	qla27xx_ग_लिखो_reg(ISPREG(vha), offset, data, buf);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t260(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uपूर्णांक offset = ent->t260.pci_offset;

	ql_dbg(ql_dbg_misc, vha, 0xd204,
	    "%s: rdpci [%lx]\n", __func__, *len);
	qla27xx_insert32(offset, buf, len);
	qla27xx_पढ़ो_reg(ISPREG(vha), offset, buf, len);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t261(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uपूर्णांक offset = ent->t261.pci_offset;
	uदीर्घ data = le32_to_cpu(ent->t261.ग_लिखो_data);

	ql_dbg(ql_dbg_misc, vha, 0xd205,
	    "%s: wrpci [%lx]\n", __func__, *len);
	qla27xx_ग_लिखो_reg(ISPREG(vha), offset, data, buf);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t262(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uपूर्णांक area = ent->t262.ram_area;
	uदीर्घ start = le32_to_cpu(ent->t262.start_addr);
	uदीर्घ end = le32_to_cpu(ent->t262.end_addr);
	uदीर्घ dwords;
	पूर्णांक rc;

	ql_dbg(ql_dbg_misc, vha, 0xd206,
	    "%s: rdram(%x) [%lx]\n", __func__, ent->t262.ram_area, *len);

	अगर (area == T262_RAM_AREA_CRITICAL_RAM) अणु
		;
	पूर्ण अन्यथा अगर (area == T262_RAM_AREA_EXTERNAL_RAM) अणु
		end = vha->hw->fw_memory_size;
		अगर (buf)
			ent->t262.end_addr = cpu_to_le32(end);
	पूर्ण अन्यथा अगर (area == T262_RAM_AREA_SHARED_RAM) अणु
		start = vha->hw->fw_shared_ram_start;
		end = vha->hw->fw_shared_ram_end;
		अगर (buf) अणु
			ent->t262.start_addr = cpu_to_le32(start);
			ent->t262.end_addr = cpu_to_le32(end);
		पूर्ण
	पूर्ण अन्यथा अगर (area == T262_RAM_AREA_DDR_RAM) अणु
		start = vha->hw->fw_ddr_ram_start;
		end = vha->hw->fw_ddr_ram_end;
		अगर (buf) अणु
			ent->t262.start_addr = cpu_to_le32(start);
			ent->t262.end_addr = cpu_to_le32(end);
		पूर्ण
	पूर्ण अन्यथा अगर (area == T262_RAM_AREA_MISC) अणु
		अगर (buf) अणु
			ent->t262.start_addr = cpu_to_le32(start);
			ent->t262.end_addr = cpu_to_le32(end);
		पूर्ण
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_misc, vha, 0xd022,
		    "%s: unknown area %x\n", __func__, area);
		qla27xx_skip_entry(ent, buf);
		जाओ करोne;
	पूर्ण

	अगर (end < start || start == 0 || end == 0) अणु
		ql_dbg(ql_dbg_misc, vha, 0xd023,
		    "%s: unusable range (start=%lx end=%lx)\n",
		    __func__, start, end);
		qla27xx_skip_entry(ent, buf);
		जाओ करोne;
	पूर्ण

	dwords = end - start + 1;
	अगर (buf) अणु
		buf += *len;
		rc = qla24xx_dump_ram(vha->hw, start, buf, dwords, &buf);
		अगर (rc != QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_async, vha, 0xffff,
			    "%s: dump ram MB failed. Area %xh start %lxh end %lxh\n",
			    __func__, area, start, end);
			वापस INVALID_ENTRY;
		पूर्ण
	पूर्ण
	*len += dwords * माप(uपूर्णांक32_t);
करोne:
	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t263(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uपूर्णांक type = ent->t263.queue_type;
	uपूर्णांक count = 0;
	uपूर्णांक i;
	uपूर्णांक length;

	ql_dbg(ql_dbg_misc + ql_dbg_verbose, vha, 0xd207,
	    "%s: getq(%x) [%lx]\n", __func__, type, *len);
	अगर (type == T263_QUEUE_TYPE_REQ) अणु
		क्रम (i = 0; i < vha->hw->max_req_queues; i++) अणु
			काष्ठा req_que *req = vha->hw->req_q_map[i];

			अगर (req || !buf) अणु
				length = req ?
				    req->length : REQUEST_ENTRY_CNT_24XX;
				qla27xx_insert16(i, buf, len);
				qla27xx_insert16(length, buf, len);
				qla27xx_insertbuf(req ? req->ring : शून्य,
				    length * माप(*req->ring), buf, len);
				count++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (type == T263_QUEUE_TYPE_RSP) अणु
		क्रम (i = 0; i < vha->hw->max_rsp_queues; i++) अणु
			काष्ठा rsp_que *rsp = vha->hw->rsp_q_map[i];

			अगर (rsp || !buf) अणु
				length = rsp ?
				    rsp->length : RESPONSE_ENTRY_CNT_MQ;
				qla27xx_insert16(i, buf, len);
				qla27xx_insert16(length, buf, len);
				qla27xx_insertbuf(rsp ? rsp->ring : शून्य,
				    length * माप(*rsp->ring), buf, len);
				count++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (QLA_TGT_MODE_ENABLED() &&
	    ent->t263.queue_type == T263_QUEUE_TYPE_ATIO) अणु
		काष्ठा qla_hw_data *ha = vha->hw;
		काष्ठा atio *atr = ha->tgt.atio_ring;

		अगर (atr || !buf) अणु
			length = ha->tgt.atio_q_length;
			qla27xx_insert16(0, buf, len);
			qla27xx_insert16(length, buf, len);
			qla27xx_insertbuf(atr, length * माप(*atr), buf, len);
			count++;
		पूर्ण
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_misc, vha, 0xd026,
		    "%s: unknown queue %x\n", __func__, type);
		qla27xx_skip_entry(ent, buf);
	पूर्ण

	अगर (buf) अणु
		अगर (count)
			ent->t263.num_queues = count;
		अन्यथा
			qla27xx_skip_entry(ent, buf);
	पूर्ण

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t264(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	ql_dbg(ql_dbg_misc, vha, 0xd208,
	    "%s: getfce [%lx]\n", __func__, *len);
	अगर (vha->hw->fce) अणु
		अगर (buf) अणु
			ent->t264.fce_trace_size = FCE_SIZE;
			ent->t264.ग_लिखो_poपूर्णांकer = vha->hw->fce_wr;
			ent->t264.base_poपूर्णांकer = vha->hw->fce_dma;
			ent->t264.fce_enable_mb0 = vha->hw->fce_mb[0];
			ent->t264.fce_enable_mb2 = vha->hw->fce_mb[2];
			ent->t264.fce_enable_mb3 = vha->hw->fce_mb[3];
			ent->t264.fce_enable_mb4 = vha->hw->fce_mb[4];
			ent->t264.fce_enable_mb5 = vha->hw->fce_mb[5];
			ent->t264.fce_enable_mb6 = vha->hw->fce_mb[6];
		पूर्ण
		qla27xx_insertbuf(vha->hw->fce, FCE_SIZE, buf, len);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_misc, vha, 0xd027,
		    "%s: missing fce\n", __func__);
		qla27xx_skip_entry(ent, buf);
	पूर्ण

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t265(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	ql_dbg(ql_dbg_misc + ql_dbg_verbose, vha, 0xd209,
	    "%s: pause risc [%lx]\n", __func__, *len);
	अगर (buf)
		qla24xx_छोड़ो_risc(ISPREG(vha), vha->hw);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t266(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	ql_dbg(ql_dbg_misc, vha, 0xd20a,
	    "%s: reset risc [%lx]\n", __func__, *len);
	अगर (buf)
		WARN_ON_ONCE(qla24xx_soft_reset(vha->hw) != QLA_SUCCESS);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t267(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uपूर्णांक offset = ent->t267.pci_offset;
	uदीर्घ data = le32_to_cpu(ent->t267.data);

	ql_dbg(ql_dbg_misc, vha, 0xd20b,
	    "%s: dis intr [%lx]\n", __func__, *len);
	qla27xx_ग_लिखो_reg(ISPREG(vha), offset, data, buf);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t268(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	ql_dbg(ql_dbg_misc, vha, 0xd20c,
	    "%s: gethb(%x) [%lx]\n", __func__, ent->t268.buf_type, *len);
	चयन (ent->t268.buf_type) अणु
	हाल T268_BUF_TYPE_EXTD_TRACE:
		अगर (vha->hw->eft) अणु
			अगर (buf) अणु
				ent->t268.buf_size = EFT_SIZE;
				ent->t268.start_addr = vha->hw->eft_dma;
			पूर्ण
			qla27xx_insertbuf(vha->hw->eft, EFT_SIZE, buf, len);
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_misc, vha, 0xd028,
			    "%s: missing eft\n", __func__);
			qla27xx_skip_entry(ent, buf);
		पूर्ण
		अवरोध;
	हाल T268_BUF_TYPE_EXCH_BUFOFF:
		अगर (vha->hw->exchoffld_buf) अणु
			अगर (buf) अणु
				ent->t268.buf_size = vha->hw->exchoffld_size;
				ent->t268.start_addr =
					vha->hw->exchoffld_buf_dma;
			पूर्ण
			qla27xx_insertbuf(vha->hw->exchoffld_buf,
			    vha->hw->exchoffld_size, buf, len);
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_misc, vha, 0xd028,
			    "%s: missing exch offld\n", __func__);
			qla27xx_skip_entry(ent, buf);
		पूर्ण
		अवरोध;
	हाल T268_BUF_TYPE_EXTD_LOGIN:
		अगर (vha->hw->exlogin_buf) अणु
			अगर (buf) अणु
				ent->t268.buf_size = vha->hw->exlogin_size;
				ent->t268.start_addr =
					vha->hw->exlogin_buf_dma;
			पूर्ण
			qla27xx_insertbuf(vha->hw->exlogin_buf,
			    vha->hw->exlogin_size, buf, len);
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_misc, vha, 0xd028,
			    "%s: missing ext login\n", __func__);
			qla27xx_skip_entry(ent, buf);
		पूर्ण
		अवरोध;

	हाल T268_BUF_TYPE_REQ_MIRROR:
	हाल T268_BUF_TYPE_RSP_MIRROR:
		/*
		 * Mirror poपूर्णांकers are not implemented in the
		 * driver, instead shaकरोw poपूर्णांकers are used by
		 * the drier. Skip these entries.
		 */
		qla27xx_skip_entry(ent, buf);
		अवरोध;
	शेष:
		ql_dbg(ql_dbg_async, vha, 0xd02b,
		    "%s: unknown buffer %x\n", __func__, ent->t268.buf_type);
		qla27xx_skip_entry(ent, buf);
		अवरोध;
	पूर्ण

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t269(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	ql_dbg(ql_dbg_misc, vha, 0xd20d,
	    "%s: scratch [%lx]\n", __func__, *len);
	qla27xx_insert32(0xaaaaaaaa, buf, len);
	qla27xx_insert32(0xbbbbbbbb, buf, len);
	qla27xx_insert32(0xcccccccc, buf, len);
	qla27xx_insert32(0xdddddddd, buf, len);
	qla27xx_insert32(*len + माप(uपूर्णांक32_t), buf, len);
	अगर (buf)
		ent->t269.scratch_size = 5 * माप(uपूर्णांक32_t);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t270(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ addr = le32_to_cpu(ent->t270.addr);
	uदीर्घ dwords = le32_to_cpu(ent->t270.count);

	ql_dbg(ql_dbg_misc, vha, 0xd20e,
	    "%s: rdremreg [%lx]\n", __func__, *len);
	qla27xx_ग_लिखो_reg(ISPREG(vha), IOBASE_ADDR, 0x40, buf);
	जबतक (dwords--) अणु
		qla27xx_ग_लिखो_reg(ISPREG(vha), 0xc0, addr|0x80000000, buf);
		qla27xx_insert32(addr, buf, len);
		qla27xx_पढ़ो_reg(ISPREG(vha), 0xc4, buf, len);
		addr += माप(uपूर्णांक32_t);
	पूर्ण

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t271(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ addr = le32_to_cpu(ent->t271.addr);
	uदीर्घ data = le32_to_cpu(ent->t271.data);

	ql_dbg(ql_dbg_misc, vha, 0xd20f,
	    "%s: wrremreg [%lx]\n", __func__, *len);
	qla27xx_ग_लिखो_reg(ISPREG(vha), IOBASE(vha), 0x40, buf);
	qla27xx_ग_लिखो_reg(ISPREG(vha), 0xc4, data, buf);
	qla27xx_ग_लिखो_reg(ISPREG(vha), 0xc0, addr, buf);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t272(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ dwords = le32_to_cpu(ent->t272.count);
	uदीर्घ start = le32_to_cpu(ent->t272.addr);

	ql_dbg(ql_dbg_misc, vha, 0xd210,
	    "%s: rdremram [%lx]\n", __func__, *len);
	अगर (buf) अणु
		ql_dbg(ql_dbg_misc, vha, 0xd02c,
		    "%s: @%lx -> (%lx dwords)\n", __func__, start, dwords);
		buf += *len;
		qla27xx_dump_mpi_ram(vha->hw, start, buf, dwords, &buf);
	पूर्ण
	*len += dwords * माप(uपूर्णांक32_t);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t273(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ dwords = le32_to_cpu(ent->t273.count);
	uदीर्घ addr = le32_to_cpu(ent->t273.addr);
	uपूर्णांक32_t value;

	ql_dbg(ql_dbg_misc, vha, 0xd211,
	    "%s: pcicfg [%lx]\n", __func__, *len);
	जबतक (dwords--) अणु
		value = ~0;
		अगर (pci_पढ़ो_config_dword(vha->hw->pdev, addr, &value))
			ql_dbg(ql_dbg_misc, vha, 0xd02d,
			    "%s: failed pcicfg read at %lx\n", __func__, addr);
		qla27xx_insert32(addr, buf, len);
		qla27xx_insert32(value, buf, len);
		addr += माप(uपूर्णांक32_t);
	पूर्ण

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t274(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ type = ent->t274.queue_type;
	uपूर्णांक count = 0;
	uपूर्णांक i;

	ql_dbg(ql_dbg_misc + ql_dbg_verbose, vha, 0xd212,
	    "%s: getqsh(%lx) [%lx]\n", __func__, type, *len);
	अगर (type == T274_QUEUE_TYPE_REQ_SHAD) अणु
		क्रम (i = 0; i < vha->hw->max_req_queues; i++) अणु
			काष्ठा req_que *req = vha->hw->req_q_map[i];

			अगर (req || !buf) अणु
				qla27xx_insert16(i, buf, len);
				qla27xx_insert16(1, buf, len);
				qla27xx_insert32(req && req->out_ptr ?
				    *req->out_ptr : 0, buf, len);
				count++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (type == T274_QUEUE_TYPE_RSP_SHAD) अणु
		क्रम (i = 0; i < vha->hw->max_rsp_queues; i++) अणु
			काष्ठा rsp_que *rsp = vha->hw->rsp_q_map[i];

			अगर (rsp || !buf) अणु
				qla27xx_insert16(i, buf, len);
				qla27xx_insert16(1, buf, len);
				qla27xx_insert32(rsp && rsp->in_ptr ?
				    *rsp->in_ptr : 0, buf, len);
				count++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (QLA_TGT_MODE_ENABLED() &&
	    ent->t274.queue_type == T274_QUEUE_TYPE_ATIO_SHAD) अणु
		काष्ठा qla_hw_data *ha = vha->hw;
		काष्ठा atio *atr = ha->tgt.atio_ring_ptr;

		अगर (atr || !buf) अणु
			qla27xx_insert16(0, buf, len);
			qla27xx_insert16(1, buf, len);
			qla27xx_insert32(ha->tgt.atio_q_in ?
			    पढ़ोl(ha->tgt.atio_q_in) : 0, buf, len);
			count++;
		पूर्ण
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_misc, vha, 0xd02f,
		    "%s: unknown queue %lx\n", __func__, type);
		qla27xx_skip_entry(ent, buf);
	पूर्ण

	अगर (buf) अणु
		अगर (count)
			ent->t274.num_queues = count;
		अन्यथा
			qla27xx_skip_entry(ent, buf);
	पूर्ण

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t275(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ offset = दुरत्व(typeof(*ent), t275.buffer);
	uदीर्घ length = le32_to_cpu(ent->t275.length);
	uदीर्घ size = le32_to_cpu(ent->hdr.size);
	व्योम *buffer = ent->t275.buffer;

	ql_dbg(ql_dbg_misc + ql_dbg_verbose, vha, 0xd213,
	    "%s: buffer(%lx) [%lx]\n", __func__, length, *len);
	अगर (!length) अणु
		ql_dbg(ql_dbg_misc, vha, 0xd020,
		    "%s: buffer zero length\n", __func__);
		qla27xx_skip_entry(ent, buf);
		जाओ करोne;
	पूर्ण
	अगर (offset + length > size) अणु
		length = size - offset;
		ql_dbg(ql_dbg_misc, vha, 0xd030,
		    "%s: buffer overflow, truncate [%lx]\n", __func__, length);
		ent->t275.length = cpu_to_le32(length);
	पूर्ण

	qla27xx_insertbuf(buffer, length, buf, len);
करोne:
	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t276(काष्ठा scsi_qla_host *vha,
    काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	ql_dbg(ql_dbg_misc + ql_dbg_verbose, vha, 0xd214,
	    "%s: cond [%lx]\n", __func__, *len);

	अगर (buf) अणु
		uदीर्घ cond1 = le32_to_cpu(ent->t276.cond1);
		uदीर्घ cond2 = le32_to_cpu(ent->t276.cond2);
		uपूर्णांक type = vha->hw->pdev->device >> 4 & 0xf;
		uपूर्णांक func = vha->hw->port_no & 0x3;

		अगर (type != cond1 || func != cond2) अणु
			काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp = buf;

			पंचांगp->count--;
			ent = qla27xx_next_entry(ent);
			qla27xx_skip_entry(ent, buf);
		पूर्ण
	पूर्ण

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t277(काष्ठा scsi_qla_host *vha,
    काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ cmd_addr = le32_to_cpu(ent->t277.cmd_addr);
	uदीर्घ wr_cmd_data = le32_to_cpu(ent->t277.wr_cmd_data);
	uदीर्घ data_addr = le32_to_cpu(ent->t277.data_addr);

	ql_dbg(ql_dbg_misc + ql_dbg_verbose, vha, 0xd215,
	    "%s: rdpep [%lx]\n", __func__, *len);
	qla27xx_insert32(wr_cmd_data, buf, len);
	qla27xx_ग_लिखो_reg(ISPREG(vha), cmd_addr, wr_cmd_data, buf);
	qla27xx_पढ़ो_reg(ISPREG(vha), data_addr, buf, len);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_t278(काष्ठा scsi_qla_host *vha,
    काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ cmd_addr = le32_to_cpu(ent->t278.cmd_addr);
	uदीर्घ wr_cmd_data = le32_to_cpu(ent->t278.wr_cmd_data);
	uदीर्घ data_addr = le32_to_cpu(ent->t278.data_addr);
	uदीर्घ wr_data = le32_to_cpu(ent->t278.wr_data);

	ql_dbg(ql_dbg_misc + ql_dbg_verbose, vha, 0xd216,
	    "%s: wrpep [%lx]\n", __func__, *len);
	qla27xx_ग_लिखो_reg(ISPREG(vha), data_addr, wr_data, buf);
	qla27xx_ग_लिखो_reg(ISPREG(vha), cmd_addr, wr_cmd_data, buf);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा qla27xx_fwdt_entry *
qla27xx_fwdt_entry_other(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_entry *ent, व्योम *buf, uदीर्घ *len)
अणु
	uदीर्घ type = le32_to_cpu(ent->hdr.type);

	ql_dbg(ql_dbg_misc, vha, 0xd2ff,
	    "%s: other %lx [%lx]\n", __func__, type, *len);
	qla27xx_skip_entry(ent, buf);

	वापस qla27xx_next_entry(ent);
पूर्ण

अटल काष्ठा अणु
	uपूर्णांक type;
	typeof(qla27xx_fwdt_entry_other)(*call);
पूर्ण qla27xx_fwdt_entry_call[] = अणु
	अणु ENTRY_TYPE_NOP,		qla27xx_fwdt_entry_t0    पूर्ण,
	अणु ENTRY_TYPE_TMP_END,		qla27xx_fwdt_entry_t255  पूर्ण,
	अणु ENTRY_TYPE_RD_IOB_T1,		qla27xx_fwdt_entry_t256  पूर्ण,
	अणु ENTRY_TYPE_WR_IOB_T1,		qla27xx_fwdt_entry_t257  पूर्ण,
	अणु ENTRY_TYPE_RD_IOB_T2,		qla27xx_fwdt_entry_t258  पूर्ण,
	अणु ENTRY_TYPE_WR_IOB_T2,		qla27xx_fwdt_entry_t259  पूर्ण,
	अणु ENTRY_TYPE_RD_PCI,		qla27xx_fwdt_entry_t260  पूर्ण,
	अणु ENTRY_TYPE_WR_PCI,		qla27xx_fwdt_entry_t261  पूर्ण,
	अणु ENTRY_TYPE_RD_RAM,		qla27xx_fwdt_entry_t262  पूर्ण,
	अणु ENTRY_TYPE_GET_QUEUE,		qla27xx_fwdt_entry_t263  पूर्ण,
	अणु ENTRY_TYPE_GET_FCE,		qla27xx_fwdt_entry_t264  पूर्ण,
	अणु ENTRY_TYPE_PSE_RISC,		qla27xx_fwdt_entry_t265  पूर्ण,
	अणु ENTRY_TYPE_RST_RISC,		qla27xx_fwdt_entry_t266  पूर्ण,
	अणु ENTRY_TYPE_DIS_INTR,		qla27xx_fwdt_entry_t267  पूर्ण,
	अणु ENTRY_TYPE_GET_HBUF,		qla27xx_fwdt_entry_t268  पूर्ण,
	अणु ENTRY_TYPE_SCRATCH,		qla27xx_fwdt_entry_t269  पूर्ण,
	अणु ENTRY_TYPE_RDREMREG,		qla27xx_fwdt_entry_t270  पूर्ण,
	अणु ENTRY_TYPE_WRREMREG,		qla27xx_fwdt_entry_t271  पूर्ण,
	अणु ENTRY_TYPE_RDREMRAM,		qla27xx_fwdt_entry_t272  पूर्ण,
	अणु ENTRY_TYPE_PCICFG,		qla27xx_fwdt_entry_t273  पूर्ण,
	अणु ENTRY_TYPE_GET_SHADOW,	qla27xx_fwdt_entry_t274  पूर्ण,
	अणु ENTRY_TYPE_WRITE_BUF,		qla27xx_fwdt_entry_t275  पूर्ण,
	अणु ENTRY_TYPE_CONDITIONAL,	qla27xx_fwdt_entry_t276  पूर्ण,
	अणु ENTRY_TYPE_RDPEPREG,		qla27xx_fwdt_entry_t277  पूर्ण,
	अणु ENTRY_TYPE_WRPEPREG,		qla27xx_fwdt_entry_t278  पूर्ण,
	अणु -1,				qla27xx_fwdt_entry_other पूर्ण
पूर्ण;

अटल अंतरभूत
typeof(qla27xx_fwdt_entry_call->call)(qla27xx_find_entry(uपूर्णांक type))
अणु
	typeof(*qla27xx_fwdt_entry_call) *list = qla27xx_fwdt_entry_call;

	जबतक (list->type < type)
		list++;

	अगर (list->type == type)
		वापस list->call;
	वापस qla27xx_fwdt_entry_other;
पूर्ण

अटल व्योम
qla27xx_walk_ढाँचा(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp, व्योम *buf, uदीर्घ *len)
अणु
	काष्ठा qla27xx_fwdt_entry *ent = (व्योम *)पंचांगp +
	    le32_to_cpu(पंचांगp->entry_offset);
	uदीर्घ type;

	पंचांगp->count = le32_to_cpu(पंचांगp->entry_count);
	ql_dbg(ql_dbg_misc, vha, 0xd01a,
	    "%s: entry count %u\n", __func__, पंचांगp->count);
	जबतक (ent && पंचांगp->count--) अणु
		type = le32_to_cpu(ent->hdr.type);
		ent = qla27xx_find_entry(type)(vha, ent, buf, len);
		अगर (!ent)
			अवरोध;

		अगर (ent == INVALID_ENTRY) अणु
			*len = 0;
			ql_dbg(ql_dbg_async, vha, 0xffff,
			    "Unable to capture FW dump");
			जाओ bailout;
		पूर्ण
	पूर्ण

	अगर (पंचांगp->count)
		ql_dbg(ql_dbg_misc, vha, 0xd018,
		    "%s: entry count residual=+%u\n", __func__, पंचांगp->count);

	अगर (ent)
		ql_dbg(ql_dbg_misc, vha, 0xd019,
		    "%s: missing end entry\n", __func__);

bailout:
	cpu_to_le32s(&पंचांगp->count);	/* endianize residual count */
पूर्ण

अटल व्योम
qla27xx_समय_stamp(काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp)
अणु
	पंचांगp->capture_बारtamp = cpu_to_le32(jअगरfies);
पूर्ण

अटल व्योम
qla27xx_driver_info(काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp)
अणु
	uपूर्णांक8_t v[] = अणु 0, 0, 0, 0, 0, 0 पूर्ण;

	WARN_ON_ONCE(माला_पूछो(qla2x00_version_str,
			    "%hhu.%hhu.%hhu.%hhu",
			    v + 0, v + 1, v + 2, v + 3) != 4);

	पंचांगp->driver_info[0] = cpu_to_le32(
		v[3] << 24 | v[2] << 16 | v[1] << 8 | v[0]);
	पंचांगp->driver_info[1] = cpu_to_le32(v[5] << 8 | v[4]);
	पंचांगp->driver_info[2] = __स्थिरant_cpu_to_le32(0x12345678);
पूर्ण

अटल व्योम
qla27xx_firmware_info(काष्ठा scsi_qla_host *vha,
    काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp)
अणु
	पंचांगp->firmware_version[0] = cpu_to_le32(vha->hw->fw_major_version);
	पंचांगp->firmware_version[1] = cpu_to_le32(vha->hw->fw_minor_version);
	पंचांगp->firmware_version[2] = cpu_to_le32(vha->hw->fw_subminor_version);
	पंचांगp->firmware_version[3] = cpu_to_le32(
		vha->hw->fw_attributes_h << 16 | vha->hw->fw_attributes);
	पंचांगp->firmware_version[4] = cpu_to_le32(
	  vha->hw->fw_attributes_ext[1] << 16 | vha->hw->fw_attributes_ext[0]);
पूर्ण

अटल व्योम
ql27xx_edit_ढाँचा(काष्ठा scsi_qla_host *vha,
	काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp)
अणु
	qla27xx_समय_stamp(पंचांगp);
	qla27xx_driver_info(पंचांगp);
	qla27xx_firmware_info(vha, पंचांगp);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
qla27xx_ढाँचा_checksum(व्योम *p, uदीर्घ size)
अणु
	__le32 *buf = p;
	uपूर्णांक64_t sum = 0;

	size /= माप(*buf);

	क्रम ( ; size--; buf++)
		sum += le32_to_cpu(*buf);

	sum = (sum & 0xffffffff) + (sum >> 32);

	वापस ~sum;
पूर्ण

अटल अंतरभूत पूर्णांक
qla27xx_verअगरy_ढाँचा_checksum(काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp)
अणु
	वापस qla27xx_ढाँचा_checksum(पंचांगp,
		le32_to_cpu(पंचांगp->ढाँचा_size)) == 0;
पूर्ण

अटल अंतरभूत पूर्णांक
qla27xx_verअगरy_ढाँचा_header(काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp)
अणु
	वापस le32_to_cpu(पंचांगp->ढाँचा_type) == TEMPLATE_TYPE_FWDUMP;
पूर्ण

अटल uदीर्घ
qla27xx_execute_fwdt_ढाँचा(काष्ठा scsi_qla_host *vha,
    काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp, व्योम *buf)
अणु
	uदीर्घ len = 0;

	अगर (qla27xx_fwdt_ढाँचा_valid(पंचांगp)) अणु
		len = le32_to_cpu(पंचांगp->ढाँचा_size);
		पंचांगp = स_नकल(buf, पंचांगp, len);
		ql27xx_edit_ढाँचा(vha, पंचांगp);
		qla27xx_walk_ढाँचा(vha, पंचांगp, buf, &len);
	पूर्ण

	वापस len;
पूर्ण

uदीर्घ
qla27xx_fwdt_calculate_dump_size(काष्ठा scsi_qla_host *vha, व्योम *p)
अणु
	काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp = p;
	uदीर्घ len = 0;

	अगर (qla27xx_fwdt_ढाँचा_valid(पंचांगp)) अणु
		len = le32_to_cpu(पंचांगp->ढाँचा_size);
		qla27xx_walk_ढाँचा(vha, पंचांगp, शून्य, &len);
	पूर्ण

	वापस len;
पूर्ण

uदीर्घ
qla27xx_fwdt_ढाँचा_size(व्योम *p)
अणु
	काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp = p;

	वापस le32_to_cpu(पंचांगp->ढाँचा_size);
पूर्ण

पूर्णांक
qla27xx_fwdt_ढाँचा_valid(व्योम *p)
अणु
	काष्ठा qla27xx_fwdt_ढाँचा *पंचांगp = p;

	अगर (!qla27xx_verअगरy_ढाँचा_header(पंचांगp)) अणु
		ql_log(ql_log_warn, शून्य, 0xd01c,
		    "%s: template type %x\n", __func__,
		    le32_to_cpu(पंचांगp->ढाँचा_type));
		वापस false;
	पूर्ण

	अगर (!qla27xx_verअगरy_ढाँचा_checksum(पंचांगp)) अणु
		ql_log(ql_log_warn, शून्य, 0xd01d,
		    "%s: failed template checksum\n", __func__);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम
qla27xx_mpi_fwdump(scsi_qla_host_t *vha, पूर्णांक hardware_locked)
अणु
	uदीर्घ flags = 0;

	अगर (!hardware_locked)
		spin_lock_irqsave(&vha->hw->hardware_lock, flags);
	अगर (!vha->hw->mpi_fw_dump) अणु
		ql_log(ql_log_warn, vha, 0x02f3, "-> mpi_fwdump no buffer\n");
	पूर्ण अन्यथा अणु
		काष्ठा fwdt *fwdt = &vha->hw->fwdt[1];
		uदीर्घ len;
		व्योम *buf = vha->hw->mpi_fw_dump;
		bool walk_ढाँचा_only = false;

		अगर (vha->hw->mpi_fw_dumped) अणु
			/* Use the spare area क्रम any further dumps. */
			buf += fwdt->dump_size;
			walk_ढाँचा_only = true;
			ql_log(ql_log_warn, vha, 0x02f4,
			       "-> MPI firmware already dumped -- dump saving to temporary buffer %p.\n",
			       buf);
		पूर्ण

		ql_log(ql_log_warn, vha, 0x02f5, "-> fwdt1 running...\n");
		अगर (!fwdt->ढाँचा) अणु
			ql_log(ql_log_warn, vha, 0x02f6,
			       "-> fwdt1 no template\n");
			जाओ bailout;
		पूर्ण
		len = qla27xx_execute_fwdt_ढाँचा(vha, fwdt->ढाँचा, buf);
		अगर (len == 0) अणु
			जाओ bailout;
		पूर्ण अन्यथा अगर (len != fwdt->dump_size) अणु
			ql_log(ql_log_warn, vha, 0x02f7,
			       "-> fwdt1 fwdump residual=%+ld\n",
			       fwdt->dump_size - len);
		पूर्ण
		vha->hw->stat.num_mpi_reset++;
		अगर (walk_ढाँचा_only)
			जाओ bailout;

		vha->hw->mpi_fw_dump_len = len;
		vha->hw->mpi_fw_dumped = 1;

		ql_log(ql_log_warn, vha, 0x02f8,
		       "-> MPI firmware dump saved to buffer (%lu/%p)\n",
		       vha->host_no, vha->hw->mpi_fw_dump);
		qla2x00_post_uevent_work(vha, QLA_UEVENT_CODE_FW_DUMP);
	पूर्ण

bailout:
	अगर (!hardware_locked)
		spin_unlock_irqrestore(&vha->hw->hardware_lock, flags);
पूर्ण

व्योम
qla27xx_fwdump(scsi_qla_host_t *vha)
अणु
	lockdep_निश्चित_held(&vha->hw->hardware_lock);

	अगर (!vha->hw->fw_dump) अणु
		ql_log(ql_log_warn, vha, 0xd01e, "-> fwdump no buffer\n");
	पूर्ण अन्यथा अगर (vha->hw->fw_dumped) अणु
		ql_log(ql_log_warn, vha, 0xd01f,
		    "-> Firmware already dumped (%p) -- ignoring request\n",
		    vha->hw->fw_dump);
	पूर्ण अन्यथा अणु
		काष्ठा fwdt *fwdt = vha->hw->fwdt;
		uदीर्घ len;
		व्योम *buf = vha->hw->fw_dump;

		ql_log(ql_log_warn, vha, 0xd011, "-> fwdt0 running...\n");
		अगर (!fwdt->ढाँचा) अणु
			ql_log(ql_log_warn, vha, 0xd012,
			       "-> fwdt0 no template\n");
			वापस;
		पूर्ण
		len = qla27xx_execute_fwdt_ढाँचा(vha, fwdt->ढाँचा, buf);
		अगर (len == 0) अणु
			वापस;
		पूर्ण अन्यथा अगर (len != fwdt->dump_size) अणु
			ql_log(ql_log_warn, vha, 0xd013,
			       "-> fwdt0 fwdump residual=%+ld\n",
				fwdt->dump_size - len);
		पूर्ण

		vha->hw->fw_dump_len = len;
		vha->hw->fw_dumped = true;

		ql_log(ql_log_warn, vha, 0xd015,
		    "-> Firmware dump saved to buffer (%lu/%p) <%lx>\n",
		    vha->host_no, vha->hw->fw_dump, vha->hw->fw_dump_cap_flags);
		qla2x00_post_uevent_work(vha, QLA_UEVENT_CODE_FW_DUMP);
	पूर्ण
पूर्ण
