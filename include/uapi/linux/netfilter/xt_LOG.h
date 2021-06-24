<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_LOG_H
#घोषणा _XT_LOG_H

/* make sure not to change this without changing nf_log.h:NF_LOG_* (!) */
#घोषणा XT_LOG_TCPSEQ		0x01	/* Log TCP sequence numbers */
#घोषणा XT_LOG_TCPOPT		0x02	/* Log TCP options */
#घोषणा XT_LOG_IPOPT		0x04	/* Log IP options */
#घोषणा XT_LOG_UID		0x08	/* Log UID owning local socket */
#घोषणा XT_LOG_NFLOG		0x10	/* Unsupported, करोn't reuse */
#घोषणा XT_LOG_MACDECODE	0x20	/* Decode MAC header */
#घोषणा XT_LOG_MASK		0x2f

काष्ठा xt_log_info अणु
	अचिन्हित अक्षर level;
	अचिन्हित अक्षर logflags;
	अक्षर prefix[30];
पूर्ण;

#पूर्ण_अगर /* _XT_LOG_H */
