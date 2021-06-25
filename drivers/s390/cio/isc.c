<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions क्रम registration of I/O पूर्णांकerruption subclasses on s390.
 *
 * Copyright IBM Corp. 2008
 * Authors: Sebastian Ott <sebott@linux.vnet.ibm.com>
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/isc.h>

अटल अचिन्हित पूर्णांक isc_refs[MAX_ISC + 1];
अटल DEFINE_SPINLOCK(isc_ref_lock);


/**
 * isc_रेजिस्टर - रेजिस्टर an I/O पूर्णांकerruption subclass.
 * @isc: I/O पूर्णांकerruption subclass to रेजिस्टर
 *
 * The number of users क्रम @isc is increased. If this is the first user to
 * रेजिस्टर @isc, the corresponding I/O पूर्णांकerruption subclass mask is enabled.
 *
 * Context:
 *   This function must not be called in पूर्णांकerrupt context.
 */
व्योम isc_रेजिस्टर(अचिन्हित पूर्णांक isc)
अणु
	अगर (isc > MAX_ISC) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	spin_lock(&isc_ref_lock);
	अगर (isc_refs[isc] == 0)
		ctl_set_bit(6, 31 - isc);
	isc_refs[isc]++;
	spin_unlock(&isc_ref_lock);
पूर्ण
EXPORT_SYMBOL_GPL(isc_रेजिस्टर);

/**
 * isc_unरेजिस्टर - unरेजिस्टर an I/O पूर्णांकerruption subclass.
 * @isc: I/O पूर्णांकerruption subclass to unरेजिस्टर
 *
 * The number of users क्रम @isc is decreased. If this is the last user to
 * unरेजिस्टर @isc, the corresponding I/O पूर्णांकerruption subclass mask is
 * disabled.
 * Note: This function must not be called अगर isc_रेजिस्टर() hasn't been called
 * beक्रमe by the driver क्रम @isc.
 *
 * Context:
 *   This function must not be called in पूर्णांकerrupt context.
 */
व्योम isc_unरेजिस्टर(अचिन्हित पूर्णांक isc)
अणु
	spin_lock(&isc_ref_lock);
	/* check क्रम misuse */
	अगर (isc > MAX_ISC || isc_refs[isc] == 0) अणु
		WARN_ON(1);
		जाओ out_unlock;
	पूर्ण
	अगर (isc_refs[isc] == 1)
		ctl_clear_bit(6, 31 - isc);
	isc_refs[isc]--;
out_unlock:
	spin_unlock(&isc_ref_lock);
पूर्ण
EXPORT_SYMBOL_GPL(isc_unरेजिस्टर);
