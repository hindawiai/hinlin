<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel(R) Trace Hub data काष्ठाures क्रम implementing buffer sinks.
 *
 * Copyright (C) 2019 Intel Corporation.
 */

#अगर_अघोषित _INTEL_TH_H_
#घोषणा _INTEL_TH_H_

#समावेश <linux/scatterlist.h>

/* MSC operating modes (MSC_MODE) */
क्रमागत अणु
	MSC_MODE_SINGLE	= 0,
	MSC_MODE_MULTI,
	MSC_MODE_EXI,
	MSC_MODE_DEBUG,
पूर्ण;

काष्ठा msu_buffer अणु
	स्थिर अक्षर	*name;
	/*
	 * ->assign() called when buffer 'mode' is set to this driver
	 *   (aka mode_store())
	 * @device:	काष्ठा device * of the msc
	 * @mode:	allows the driver to set HW mode (see the क्रमागत above)
	 * Returns:	a poपूर्णांकer to a निजी काष्ठाure associated with this
	 *		msc or शून्य in हाल of error. This निजी काष्ठाure
	 *		will then be passed पूर्णांकo all other callbacks.
	 */
	व्योम	*(*assign)(काष्ठा device *dev, पूर्णांक *mode);
	/* ->unassign():	some other mode is selected, clean up */
	व्योम	(*unassign)(व्योम *priv);
	/*
	 * ->alloc_winकरोw(): allocate memory क्रम the winकरोw of a given
	 *		size
	 * @sgt:	poपूर्णांकer to sg_table, can be overridden by the buffer
	 *		driver, or kept पूर्णांकact
	 * Returns:	number of sg table entries <= number of pages;
	 *		0 is treated as an allocation failure.
	 */
	पूर्णांक	(*alloc_winकरोw)(व्योम *priv, काष्ठा sg_table **sgt,
				माप_प्रकार size);
	व्योम	(*मुक्त_winकरोw)(व्योम *priv, काष्ठा sg_table *sgt);
	/* ->activate():	trace has started */
	व्योम	(*activate)(व्योम *priv);
	/* ->deactivate():	trace is about to stop */
	व्योम	(*deactivate)(व्योम *priv);
	/*
	 * ->पढ़ोy():	winकरोw @sgt is filled up to the last block OR
	 *		tracing is stopped by the user; this winकरोw contains
	 *		@bytes data. The winकरोw in question transitions पूर्णांकo
	 *		the "LOCKED" state, indicating that it can't be used
	 *		by hardware. To clear this state and make the winकरोw
	 *		available to the hardware again, call
	 *		पूर्णांकel_th_msc_winकरोw_unlock().
	 */
	पूर्णांक	(*पढ़ोy)(व्योम *priv, काष्ठा sg_table *sgt, माप_प्रकार bytes);
पूर्ण;

पूर्णांक पूर्णांकel_th_msu_buffer_रेजिस्टर(स्थिर काष्ठा msu_buffer *mbuf,
				 काष्ठा module *owner);
व्योम पूर्णांकel_th_msu_buffer_unरेजिस्टर(स्थिर काष्ठा msu_buffer *mbuf);
व्योम पूर्णांकel_th_msc_winकरोw_unlock(काष्ठा device *dev, काष्ठा sg_table *sgt);

#घोषणा module_पूर्णांकel_th_msu_buffer(__buffer) \
अटल पूर्णांक __init __buffer##_init(व्योम) \
अणु \
	वापस पूर्णांकel_th_msu_buffer_रेजिस्टर(&(__buffer), THIS_MODULE); \
पूर्ण \
module_init(__buffer##_init); \
अटल व्योम __निकास __buffer##_निकास(व्योम) \
अणु \
	पूर्णांकel_th_msu_buffer_unरेजिस्टर(&(__buffer)); \
पूर्ण \
module_निकास(__buffer##_निकास);

#पूर्ण_अगर /* _INTEL_TH_H_ */
