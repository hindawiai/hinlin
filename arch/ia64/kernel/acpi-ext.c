<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (c) Copyright 2003, 2006 Hewlett-Packard Development Company, L.P.
 *	Alex Williamson <alex.williamson@hp.com>
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>

#समावेश <यंत्र/acpi-ext.h>

/*
 * Device CSRs that करो not appear in PCI config space should be described
 * via ACPI.  This would normally be करोne with Address Space Descriptors
 * marked as "consumer-only," but old versions of Winकरोws and Linux ignore
 * the producer/consumer flag, so HP invented a venकरोr-defined resource to
 * describe the location and size of CSR space.
 */

काष्ठा acpi_venकरोr_uuid hp_ccsr_uuid = अणु
	.subtype = 2,
	.data = अणु 0xf9, 0xad, 0xe9, 0x69, 0x4f, 0x92, 0x5f, 0xab, 0xf6, 0x4a,
	    0x24, 0xd2, 0x01, 0x37, 0x0e, 0xad पूर्ण,
पूर्ण;

अटल acpi_status hp_ccsr_locate(acpi_handle obj, u64 *base, u64 *length)
अणु
	acpi_status status;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_resource *resource;
	काष्ठा acpi_resource_venकरोr_typed *venकरोr;

	status = acpi_get_venकरोr_resource(obj, METHOD_NAME__CRS, &hp_ccsr_uuid,
		&buffer);

	resource = buffer.poपूर्णांकer;
	venकरोr = &resource->data.venकरोr_typed;

	अगर (ACPI_FAILURE(status) || venकरोr->byte_length < 16) अणु
		status = AE_NOT_FOUND;
		जाओ निकास;
	पूर्ण

	स_नकल(base, venकरोr->byte_data, माप(*base));
	स_नकल(length, venकरोr->byte_data + 8, माप(*length));

  निकास:
	kमुक्त(buffer.poपूर्णांकer);
	वापस status;
पूर्ण

काष्ठा csr_space अणु
	u64	base;
	u64	length;
पूर्ण;

अटल acpi_status find_csr_space(काष्ठा acpi_resource *resource, व्योम *data)
अणु
	काष्ठा csr_space *space = data;
	काष्ठा acpi_resource_address64 addr;
	acpi_status status;

	status = acpi_resource_to_address64(resource, &addr);
	अगर (ACPI_SUCCESS(status) &&
	    addr.resource_type == ACPI_MEMORY_RANGE &&
	    addr.address.address_length &&
	    addr.producer_consumer == ACPI_CONSUMER) अणु
		space->base = addr.address.minimum;
		space->length = addr.address.address_length;
		वापस AE_CTRL_TERMINATE;
	पूर्ण
	वापस AE_OK;		/* keep looking */
पूर्ण

अटल acpi_status hp_crs_locate(acpi_handle obj, u64 *base, u64 *length)
अणु
	काष्ठा csr_space space = अणु 0, 0 पूर्ण;

	acpi_walk_resources(obj, METHOD_NAME__CRS, find_csr_space, &space);
	अगर (!space.length)
		वापस AE_NOT_FOUND;

	*base = space.base;
	*length = space.length;
	वापस AE_OK;
पूर्ण

acpi_status hp_acpi_csr_space(acpi_handle obj, u64 *csr_base, u64 *csr_length)
अणु
	acpi_status status;

	status = hp_ccsr_locate(obj, csr_base, csr_length);
	अगर (ACPI_SUCCESS(status))
		वापस status;

	वापस hp_crs_locate(obj, csr_base, csr_length);
पूर्ण
EXPORT_SYMBOL(hp_acpi_csr_space);
