<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * arch/घातerpc/include/यंत्र/mpic_समयr.h
 *
 * Header file क्रम Mpic Global Timer
 *
 * Copyright 2013 Freescale Semiconductor, Inc.
 *
 * Author: Wang Dongsheng <Dongsheng.Wang@मुक्तscale.com>
 *	   Li Yang <leoli@मुक्तscale.com>
 */

#अगर_अघोषित __MPIC_TIMER__
#घोषणा __MPIC_TIMER__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>

काष्ठा mpic_समयr अणु
	व्योम			*dev;
	काष्ठा cascade_priv	*cascade_handle;
	अचिन्हित पूर्णांक		num;
	अचिन्हित पूर्णांक		irq;
पूर्ण;

#अगर_घोषित CONFIG_MPIC_TIMER
काष्ठा mpic_समयr *mpic_request_समयr(irq_handler_t fn,  व्योम *dev,
		समय64_t समय);
व्योम mpic_start_समयr(काष्ठा mpic_समयr *handle);
व्योम mpic_stop_समयr(काष्ठा mpic_समयr *handle);
व्योम mpic_get_reमुख्य_समय(काष्ठा mpic_समयr *handle, समय64_t *समय);
व्योम mpic_मुक्त_समयr(काष्ठा mpic_समयr *handle);
#अन्यथा
काष्ठा mpic_समयr *mpic_request_समयr(irq_handler_t fn,  व्योम *dev,
		समय64_t समय) अणु वापस शून्य; पूर्ण
व्योम mpic_start_समयr(काष्ठा mpic_समयr *handle) अणु पूर्ण
व्योम mpic_stop_समयr(काष्ठा mpic_समयr *handle) अणु पूर्ण
व्योम mpic_get_reमुख्य_समय(काष्ठा mpic_समयr *handle, समय64_t *समय) अणु पूर्ण
व्योम mpic_मुक्त_समयr(काष्ठा mpic_समयr *handle) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
