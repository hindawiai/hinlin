<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NFIT - Machine Check Handler
 *
 * Copyright(c) 2013-2016 Intel Corporation. All rights reserved.
 */
#समावेश <linux/notअगरier.h>
#समावेश <linux/acpi.h>
#समावेश <linux/nd.h>
#समावेश <यंत्र/mce.h>
#समावेश "nfit.h"

अटल पूर्णांक nfit_handle_mce(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			व्योम *data)
अणु
	काष्ठा mce *mce = (काष्ठा mce *)data;
	काष्ठा acpi_nfit_desc *acpi_desc;
	काष्ठा nfit_spa *nfit_spa;

	/* We only care about uncorrectable memory errors */
	अगर (!mce_is_memory_error(mce) || mce_is_correctable(mce))
		वापस NOTIFY_DONE;

	/* Verअगरy the address reported in the MCE is valid. */
	अगर (!mce_usable_address(mce))
		वापस NOTIFY_DONE;

	/*
	 * mce->addr contains the physical addr accessed that caused the
	 * machine check. We need to walk through the list of NFITs, and see
	 * अगर any of them matches that address, and only then start a scrub.
	 */
	mutex_lock(&acpi_desc_lock);
	list_क्रम_each_entry(acpi_desc, &acpi_descs, list) अणु
		काष्ठा device *dev = acpi_desc->dev;
		पूर्णांक found_match = 0;

		mutex_lock(&acpi_desc->init_mutex);
		list_क्रम_each_entry(nfit_spa, &acpi_desc->spas, list) अणु
			काष्ठा acpi_nfit_प्रणाली_address *spa = nfit_spa->spa;

			अगर (nfit_spa_type(spa) != NFIT_SPA_PM)
				जारी;
			/* find the spa that covers the mce addr */
			अगर (spa->address > mce->addr)
				जारी;
			अगर ((spa->address + spa->length - 1) < mce->addr)
				जारी;
			found_match = 1;
			dev_dbg(dev, "addr in SPA %d (0x%llx, 0x%llx)\n",
				spa->range_index, spa->address, spa->length);
			/*
			 * We can अवरोध at the first match because we're going
			 * to rescan all the SPA ranges. There shouldn't be any
			 * aliasing anyway.
			 */
			अवरोध;
		पूर्ण
		mutex_unlock(&acpi_desc->init_mutex);

		अगर (!found_match)
			जारी;

		/* If this fails due to an -ENOMEM, there is little we can करो */
		nvdimm_bus_add_badrange(acpi_desc->nvdimm_bus,
				ALIGN(mce->addr, L1_CACHE_BYTES),
				L1_CACHE_BYTES);
		nvdimm_region_notअगरy(nfit_spa->nd_region,
				NVDIMM_REVALIDATE_POISON);

		अगर (acpi_desc->scrub_mode == HW_ERROR_SCRUB_ON) अणु
			/*
			 * We can ignore an -EBUSY here because अगर an ARS is
			 * alपढ़ोy in progress, just let that be the last
			 * authoritative one
			 */
			acpi_nfit_ars_rescan(acpi_desc, 0);
		पूर्ण
		mce->kflags |= MCE_HANDLED_NFIT;
		अवरोध;
	पूर्ण

	mutex_unlock(&acpi_desc_lock);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nfit_mce_dec = अणु
	.notअगरier_call	= nfit_handle_mce,
	.priority	= MCE_PRIO_NFIT,
पूर्ण;

व्योम nfit_mce_रेजिस्टर(व्योम)
अणु
	mce_रेजिस्टर_decode_chain(&nfit_mce_dec);
पूर्ण

व्योम nfit_mce_unरेजिस्टर(व्योम)
अणु
	mce_unरेजिस्टर_decode_chain(&nfit_mce_dec);
पूर्ण
