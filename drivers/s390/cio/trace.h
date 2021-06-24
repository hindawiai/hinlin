<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Tracepoपूर्णांक header क्रम the s390 Common I/O layer (CIO)
 *
 * Copyright IBM Corp. 2015
 * Author(s): Peter Oberparleiter <oberpar@linux.vnet.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/crw.h>
#समावेश <uapi/यंत्र/chpid.h>
#समावेश <uapi/यंत्र/schid.h>
#समावेश "cio.h"
#समावेश "orb.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM s390

#अगर !defined(_TRACE_S390_CIO_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_S390_CIO_H

#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(s390_class_schib,
	TP_PROTO(काष्ठा subchannel_id schid, काष्ठा schib *schib, पूर्णांक cc),
	TP_ARGS(schid, schib, cc),
	TP_STRUCT__entry(
		__field(u8, cssid)
		__field(u8, ssid)
		__field(u16, schno)
		__field(u16, devno)
		__field_काष्ठा(काष्ठा schib, schib)
		__field(u8, pmcw_ena)
		__field(u8, pmcw_st)
		__field(u8, pmcw_dnv)
		__field(u16, pmcw_dev)
		__field(u8, pmcw_lpm)
		__field(u8, pmcw_pnom)
		__field(u8, pmcw_lpum)
		__field(u8, pmcw_pim)
		__field(u8, pmcw_pam)
		__field(u8, pmcw_pom)
		__field(u64, pmcw_chpid)
		__field(पूर्णांक, cc)
	),
	TP_fast_assign(
		__entry->cssid = schid.cssid;
		__entry->ssid = schid.ssid;
		__entry->schno = schid.sch_no;
		__entry->devno = schib->pmcw.dev;
		__entry->schib = *schib;
		__entry->pmcw_ena = schib->pmcw.ena;
		__entry->pmcw_st = schib->pmcw.ena;
		__entry->pmcw_dnv = schib->pmcw.dnv;
		__entry->pmcw_dev = schib->pmcw.dev;
		__entry->pmcw_lpm = schib->pmcw.lpm;
		__entry->pmcw_pnom = schib->pmcw.pnom;
		__entry->pmcw_lpum = schib->pmcw.lpum;
		__entry->pmcw_pim = schib->pmcw.pim;
		__entry->pmcw_pam = schib->pmcw.pam;
		__entry->pmcw_pom = schib->pmcw.pom;
		स_नकल(&__entry->pmcw_chpid, &schib->pmcw.chpid, 8);
		__entry->cc = cc;
	),
	TP_prपूर्णांकk("schid=%x.%x.%04x cc=%d ena=%d st=%d dnv=%d dev=%04x "
		  "lpm=0x%02x pnom=0x%02x lpum=0x%02x pim=0x%02x pam=0x%02x "
		  "pom=0x%02x chpids=%016llx",
		  __entry->cssid, __entry->ssid, __entry->schno, __entry->cc,
		  __entry->pmcw_ena, __entry->pmcw_st,
		  __entry->pmcw_dnv, __entry->pmcw_dev,
		  __entry->pmcw_lpm, __entry->pmcw_pnom,
		  __entry->pmcw_lpum, __entry->pmcw_pim,
		  __entry->pmcw_pam, __entry->pmcw_pom,
		  __entry->pmcw_chpid
	)
);

/**
 * s390_cio_stsch -  Store Subchannel inकाष्ठाion (STSCH) was perक्रमmed
 * @schid: Subchannel ID
 * @schib: Subchannel-Inक्रमmation block
 * @cc: Condition code
 */
DEFINE_EVENT(s390_class_schib, s390_cio_stsch,
	TP_PROTO(काष्ठा subchannel_id schid, काष्ठा schib *schib, पूर्णांक cc),
	TP_ARGS(schid, schib, cc)
);

/**
 * s390_cio_msch -  Modअगरy Subchannel inकाष्ठाion (MSCH) was perक्रमmed
 * @schid: Subchannel ID
 * @schib: Subchannel-Inक्रमmation block
 * @cc: Condition code
 */
DEFINE_EVENT(s390_class_schib, s390_cio_msch,
	TP_PROTO(काष्ठा subchannel_id schid, काष्ठा schib *schib, पूर्णांक cc),
	TP_ARGS(schid, schib, cc)
);

/**
 * s390_cio_tsch - Test Subchannel inकाष्ठाion (TSCH) was perक्रमmed
 * @schid: Subchannel ID
 * @irb: Interruption-Response Block
 * @cc: Condition code
 */
TRACE_EVENT(s390_cio_tsch,
	TP_PROTO(काष्ठा subchannel_id schid, काष्ठा irb *irb, पूर्णांक cc),
	TP_ARGS(schid, irb, cc),
	TP_STRUCT__entry(
		__field(u8, cssid)
		__field(u8, ssid)
		__field(u16, schno)
		__field_काष्ठा(काष्ठा irb, irb)
		__field(u8, scsw_dcc)
		__field(u8, scsw_pno)
		__field(u8, scsw_fctl)
		__field(u8, scsw_actl)
		__field(u8, scsw_stctl)
		__field(u8, scsw_dstat)
		__field(u8, scsw_cstat)
		__field(पूर्णांक, cc)
	),
	TP_fast_assign(
		__entry->cssid = schid.cssid;
		__entry->ssid = schid.ssid;
		__entry->schno = schid.sch_no;
		__entry->irb = *irb;
		__entry->scsw_dcc = scsw_cc(&irb->scsw);
		__entry->scsw_pno = scsw_pno(&irb->scsw);
		__entry->scsw_fctl = scsw_fctl(&irb->scsw);
		__entry->scsw_actl = scsw_actl(&irb->scsw);
		__entry->scsw_stctl = scsw_stctl(&irb->scsw);
		__entry->scsw_dstat = scsw_dstat(&irb->scsw);
		__entry->scsw_cstat = scsw_cstat(&irb->scsw);
		__entry->cc = cc;
	),
	TP_prपूर्णांकk("schid=%x.%x.%04x cc=%d dcc=%d pno=%d fctl=0x%x actl=0x%x "
		  "stctl=0x%x dstat=0x%x cstat=0x%x",
		  __entry->cssid, __entry->ssid, __entry->schno, __entry->cc,
		  __entry->scsw_dcc, __entry->scsw_pno,
		  __entry->scsw_fctl, __entry->scsw_actl,
		  __entry->scsw_stctl,
		  __entry->scsw_dstat, __entry->scsw_cstat
	)
);

/**
 * s390_cio_tpi - Test Pending Interruption inकाष्ठाion (TPI) was perक्रमmed
 * @addr: Address of the I/O पूर्णांकerruption code or %शून्य
 * @cc: Condition code
 */
TRACE_EVENT(s390_cio_tpi,
	TP_PROTO(काष्ठा tpi_info *addr, पूर्णांक cc),
	TP_ARGS(addr, cc),
	TP_STRUCT__entry(
		__field(पूर्णांक, cc)
		__field_काष्ठा(काष्ठा tpi_info, tpi_info)
		__field(u8, cssid)
		__field(u8, ssid)
		__field(u16, schno)
		__field(u8, adapter_IO)
		__field(u8, isc)
		__field(u8, type)
	),
	TP_fast_assign(
		__entry->cc = cc;
		अगर (cc != 0)
			स_रखो(&__entry->tpi_info, 0, माप(काष्ठा tpi_info));
		अन्यथा अगर (addr)
			__entry->tpi_info = *addr;
		अन्यथा अणु
			स_नकल(&__entry->tpi_info, &S390_lowcore.subchannel_id,
			       माप(काष्ठा tpi_info));
		पूर्ण
		__entry->cssid = __entry->tpi_info.schid.cssid;
		__entry->ssid = __entry->tpi_info.schid.ssid;
		__entry->schno = __entry->tpi_info.schid.sch_no;
		__entry->adapter_IO = __entry->tpi_info.adapter_IO;
		__entry->isc = __entry->tpi_info.isc;
		__entry->type = __entry->tpi_info.type;
	),
	TP_prपूर्णांकk("schid=%x.%x.%04x cc=%d a=%d isc=%d type=%d",
		  __entry->cssid, __entry->ssid, __entry->schno, __entry->cc,
		  __entry->adapter_IO, __entry->isc,
		  __entry->type
	)
);

/**
 * s390_cio_ssch - Start Subchannel inकाष्ठाion (SSCH) was perक्रमmed
 * @schid: Subchannel ID
 * @orb: Operation-Request Block
 * @cc: Condition code
 */
TRACE_EVENT(s390_cio_ssch,
	TP_PROTO(काष्ठा subchannel_id schid, जोड़ orb *orb, पूर्णांक cc),
	TP_ARGS(schid, orb, cc),
	TP_STRUCT__entry(
		__field(u8, cssid)
		__field(u8, ssid)
		__field(u16, schno)
		__field_काष्ठा(जोड़ orb, orb)
		__field(पूर्णांक, cc)
	),
	TP_fast_assign(
		__entry->cssid = schid.cssid;
		__entry->ssid = schid.ssid;
		__entry->schno = schid.sch_no;
		__entry->orb = *orb;
		__entry->cc = cc;
	),
	TP_prपूर्णांकk("schid=%x.%x.%04x cc=%d", __entry->cssid, __entry->ssid,
		  __entry->schno, __entry->cc
	)
);

DECLARE_EVENT_CLASS(s390_class_schid,
	TP_PROTO(काष्ठा subchannel_id schid, पूर्णांक cc),
	TP_ARGS(schid, cc),
	TP_STRUCT__entry(
		__field(u8, cssid)
		__field(u8, ssid)
		__field(u16, schno)
		__field(पूर्णांक, cc)
	),
	TP_fast_assign(
		__entry->cssid = schid.cssid;
		__entry->ssid = schid.ssid;
		__entry->schno = schid.sch_no;
		__entry->cc = cc;
	),
	TP_prपूर्णांकk("schid=%x.%x.%04x cc=%d", __entry->cssid, __entry->ssid,
		  __entry->schno, __entry->cc
	)
);

/**
 * s390_cio_csch - Clear Subchannel inकाष्ठाion (CSCH) was perक्रमmed
 * @schid: Subchannel ID
 * @cc: Condition code
 */
DEFINE_EVENT(s390_class_schid, s390_cio_csch,
	TP_PROTO(काष्ठा subchannel_id schid, पूर्णांक cc),
	TP_ARGS(schid, cc)
);

/**
 * s390_cio_hsch - Halt Subchannel inकाष्ठाion (HSCH) was perक्रमmed
 * @schid: Subchannel ID
 * @cc: Condition code
 */
DEFINE_EVENT(s390_class_schid, s390_cio_hsch,
	TP_PROTO(काष्ठा subchannel_id schid, पूर्णांक cc),
	TP_ARGS(schid, cc)
);

/**
 * s390_cio_xsch - Cancel Subchannel inकाष्ठाion (XSCH) was perक्रमmed
 * @schid: Subchannel ID
 * @cc: Condition code
 */
DEFINE_EVENT(s390_class_schid, s390_cio_xsch,
	TP_PROTO(काष्ठा subchannel_id schid, पूर्णांक cc),
	TP_ARGS(schid, cc)
);

/**
 * s390_cio_rsch - Resume Subchannel inकाष्ठाion (RSCH) was perक्रमmed
 * @schid: Subchannel ID
 * @cc: Condition code
 */
DEFINE_EVENT(s390_class_schid, s390_cio_rsch,
	TP_PROTO(काष्ठा subchannel_id schid, पूर्णांक cc),
	TP_ARGS(schid, cc)
);

#घोषणा CHSC_MAX_REQUEST_LEN		64
#घोषणा CHSC_MAX_RESPONSE_LEN		64

/**
 * s390_cio_chsc - Channel Subप्रणाली Call (CHSC) inकाष्ठाion was perक्रमmed
 * @chsc: CHSC block
 * @cc: Condition code
 */
TRACE_EVENT(s390_cio_chsc,
	TP_PROTO(काष्ठा chsc_header *chsc, पूर्णांक cc),
	TP_ARGS(chsc, cc),
	TP_STRUCT__entry(
		__field(पूर्णांक, cc)
		__field(u16, code)
		__field(u16, rcode)
		__array(u8, request, CHSC_MAX_REQUEST_LEN)
		__array(u8, response, CHSC_MAX_RESPONSE_LEN)
	),
	TP_fast_assign(
		__entry->cc = cc;
		__entry->code = chsc->code;
		स_नकल(&entry->request, chsc,
		       min_t(u16, chsc->length, CHSC_MAX_REQUEST_LEN));
		chsc = (काष्ठा chsc_header *) ((अक्षर *) chsc + chsc->length);
		__entry->rcode = chsc->code;
		स_नकल(&entry->response, chsc,
		       min_t(u16, chsc->length, CHSC_MAX_RESPONSE_LEN));
	),
	TP_prपूर्णांकk("code=0x%04x cc=%d rcode=0x%04x", __entry->code,
		  __entry->cc, __entry->rcode)
);

/**
 * s390_cio_पूर्णांकerrupt - An I/O पूर्णांकerrupt occurred
 * @tpi_info: Address of the I/O पूर्णांकerruption code
 */
TRACE_EVENT(s390_cio_पूर्णांकerrupt,
	TP_PROTO(काष्ठा tpi_info *tpi_info),
	TP_ARGS(tpi_info),
	TP_STRUCT__entry(
		__field_काष्ठा(काष्ठा tpi_info, tpi_info)
		__field(u8, cssid)
		__field(u8, ssid)
		__field(u16, schno)
		__field(u8, isc)
		__field(u8, type)
	),
	TP_fast_assign(
		__entry->tpi_info = *tpi_info;
		__entry->cssid = tpi_info->schid.cssid;
		__entry->ssid = tpi_info->schid.ssid;
		__entry->schno = tpi_info->schid.sch_no;
		__entry->isc = tpi_info->isc;
		__entry->type = tpi_info->type;
	),
	TP_prपूर्णांकk("schid=%x.%x.%04x isc=%d type=%d",
		  __entry->cssid, __entry->ssid, __entry->schno,
		  __entry->isc, __entry->type
	)
);

/**
 * s390_cio_adapter_पूर्णांक - An adapter पूर्णांकerrupt occurred
 * @tpi_info: Address of the I/O पूर्णांकerruption code
 */
TRACE_EVENT(s390_cio_adapter_पूर्णांक,
	TP_PROTO(काष्ठा tpi_info *tpi_info),
	TP_ARGS(tpi_info),
	TP_STRUCT__entry(
		__field_काष्ठा(काष्ठा tpi_info, tpi_info)
		__field(u8, isc)
	),
	TP_fast_assign(
		__entry->tpi_info = *tpi_info;
		__entry->isc = tpi_info->isc;
	),
	TP_prपूर्णांकk("isc=%d", __entry->isc)
);

/**
 * s390_cio_stcrw - Store Channel Report Word (STCRW) was perक्रमmed
 * @crw: Channel Report Word
 * @cc: Condition code
 */
TRACE_EVENT(s390_cio_stcrw,
	TP_PROTO(काष्ठा crw *crw, पूर्णांक cc),
	TP_ARGS(crw, cc),
	TP_STRUCT__entry(
		__field_काष्ठा(काष्ठा crw, crw)
		__field(पूर्णांक, cc)
		__field(u8, slct)
		__field(u8, oflw)
		__field(u8, chn)
		__field(u8, rsc)
		__field(u8, anc)
		__field(u8, erc)
		__field(u16, rsid)
	),
	TP_fast_assign(
		__entry->crw = *crw;
		__entry->cc = cc;
		__entry->slct = crw->slct;
		__entry->oflw = crw->oflw;
		__entry->chn = crw->chn;
		__entry->rsc = crw->rsc;
		__entry->anc = crw->anc;
		__entry->erc = crw->erc;
		__entry->rsid = crw->rsid;
	),
	TP_prपूर्णांकk("cc=%d slct=%d oflw=%d chn=%d rsc=%d anc=%d erc=0x%x "
		  "rsid=0x%x",
		  __entry->cc, __entry->slct, __entry->oflw,
		  __entry->chn, __entry->rsc,  __entry->anc,
		  __entry->erc, __entry->rsid
	)
);

#पूर्ण_अगर /* _TRACE_S390_CIO_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
