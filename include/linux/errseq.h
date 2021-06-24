<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * See Documentation/core-api/errseq.rst and lib/errseq.c
 */
#अगर_अघोषित _LINUX_ERRSEQ_H
#घोषणा _LINUX_ERRSEQ_H

प्रकार u32	errseq_t;

errseq_t errseq_set(errseq_t *eseq, पूर्णांक err);
errseq_t errseq_sample(errseq_t *eseq);
पूर्णांक errseq_check(errseq_t *eseq, errseq_t since);
पूर्णांक errseq_check_and_advance(errseq_t *eseq, errseq_t *since);
#पूर्ण_अगर
