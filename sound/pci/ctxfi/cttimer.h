<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Timer handling
 */

#अगर_अघोषित __CTTIMER_H
#घोषणा __CTTIMER_H

#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>

काष्ठा snd_pcm_substream;
काष्ठा ct_atc;
काष्ठा ct_atc_pcm;

काष्ठा ct_समयr;
काष्ठा ct_समयr_instance;

काष्ठा ct_समयr *ct_समयr_new(काष्ठा ct_atc *atc);
व्योम ct_समयr_मुक्त(काष्ठा ct_समयr *aसमयr);

काष्ठा ct_समयr_instance *
ct_समयr_instance_new(काष्ठा ct_समयr *aसमयr, काष्ठा ct_atc_pcm *apcm);
व्योम ct_समयr_instance_मुक्त(काष्ठा ct_समयr_instance *ti);
व्योम ct_समयr_start(काष्ठा ct_समयr_instance *ti);
व्योम ct_समयr_stop(काष्ठा ct_समयr_instance *ti);
व्योम ct_समयr_prepare(काष्ठा ct_समयr_instance *ti);

#पूर्ण_अगर /* __CTTIMER_H */
