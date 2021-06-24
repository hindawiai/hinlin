<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांग_zaपंचांग.h - Driver-specअगरic declarations of the ZATM driver (क्रम use by
		driver-specअगरic utilities) */

/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */


#अगर_अघोषित LINUX_ATM_ZATM_H
#घोषणा LINUX_ATM_ZATM_H

/*
 * Note: non-kernel programs including this file must also include
 * sys/types.h क्रम काष्ठा समयval
 */

#समावेश <linux/aपंचांगapi.h>
#समावेश <linux/aपंचांगioc.h>

#घोषणा ZATM_GETPOOL	_IOW('a',ATMIOC_SARPRV+1,काष्ठा aपंचांगअगर_sioc)
						/* get pool statistics */
#घोषणा ZATM_GETPOOLZ	_IOW('a',ATMIOC_SARPRV+2,काष्ठा aपंचांगअगर_sioc)
						/* get statistics and zero */
#घोषणा ZATM_SETPOOL	_IOW('a',ATMIOC_SARPRV+3,काष्ठा aपंचांगअगर_sioc)
						/* set pool parameters */

काष्ठा zaपंचांग_pool_info अणु
	पूर्णांक ref_count;			/* मुक्त buffer pool usage counters */
	पूर्णांक low_water,high_water;	/* refill parameters */
	पूर्णांक rqa_count,rqu_count;	/* queue condition counters */
	पूर्णांक offset,next_off;		/* alignment optimizations: offset */
	पूर्णांक next_cnt,next_thres;	/* repetition counter and threshold */
पूर्ण;

काष्ठा zaपंचांग_pool_req अणु
	पूर्णांक pool_num;			/* pool number */
	काष्ठा zaपंचांग_pool_info info;	/* actual inक्रमmation */
पूर्ण;

#घोषणा ZATM_OAM_POOL		0	/* मुक्त buffer pool क्रम OAM cells */
#घोषणा ZATM_AAL0_POOL		1	/* मुक्त buffer pool क्रम AAL0 cells */
#घोषणा ZATM_AAL5_POOL_BASE	2	/* first AAL5 मुक्त buffer pool */
#घोषणा ZATM_LAST_POOL	ZATM_AAL5_POOL_BASE+10 /* max. 64 kB */

#घोषणा ZATM_TIMER_HISTORY_SIZE	16	/* number of समयr adjusपंचांगents to
					   record; must be 2^n */

#पूर्ण_अगर
