<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/पन.स>
#समावेश "ipmi_si.h"

अटल अचिन्हित अक्षर port_inb(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक addr = io->addr_data;

	वापस inb(addr + (offset * io->regspacing));
पूर्ण

अटल व्योम port_outb(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset,
		      अचिन्हित अक्षर b)
अणु
	अचिन्हित पूर्णांक addr = io->addr_data;

	outb(b, addr + (offset * io->regspacing));
पूर्ण

अटल अचिन्हित अक्षर port_inw(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक addr = io->addr_data;

	वापस (inw(addr + (offset * io->regspacing)) >> io->regshअगरt) & 0xff;
पूर्ण

अटल व्योम port_outw(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset,
		      अचिन्हित अक्षर b)
अणु
	अचिन्हित पूर्णांक addr = io->addr_data;

	outw(b << io->regshअगरt, addr + (offset * io->regspacing));
पूर्ण

अटल अचिन्हित अक्षर port_inl(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक addr = io->addr_data;

	वापस (inl(addr + (offset * io->regspacing)) >> io->regshअगरt) & 0xff;
पूर्ण

अटल व्योम port_outl(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset,
		      अचिन्हित अक्षर b)
अणु
	अचिन्हित पूर्णांक addr = io->addr_data;

	outl(b << io->regshअगरt, addr+(offset * io->regspacing));
पूर्ण

अटल व्योम port_cleanup(काष्ठा si_sm_io *io)
अणु
	अचिन्हित पूर्णांक addr = io->addr_data;
	पूर्णांक          idx;

	अगर (addr) अणु
		क्रम (idx = 0; idx < io->io_size; idx++)
			release_region(addr + idx * io->regspacing,
				       io->regsize);
	पूर्ण
पूर्ण

पूर्णांक ipmi_si_port_setup(काष्ठा si_sm_io *io)
अणु
	अचिन्हित पूर्णांक addr = io->addr_data;
	पूर्णांक          idx;

	अगर (!addr)
		वापस -ENODEV;

	/*
	 * Figure out the actual inb/inw/inl/etc routine to use based
	 * upon the रेजिस्टर size.
	 */
	चयन (io->regsize) अणु
	हाल 1:
		io->inputb = port_inb;
		io->outputb = port_outb;
		अवरोध;
	हाल 2:
		io->inputb = port_inw;
		io->outputb = port_outw;
		अवरोध;
	हाल 4:
		io->inputb = port_inl;
		io->outputb = port_outl;
		अवरोध;
	शेष:
		dev_warn(io->dev, "Invalid register size: %d\n",
			 io->regsize);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Some BIOSes reserve disjoपूर्णांक I/O regions in their ACPI
	 * tables.  This causes problems when trying to रेजिस्टर the
	 * entire I/O region.  Thereक्रमe we must रेजिस्टर each I/O
	 * port separately.
	 */
	क्रम (idx = 0; idx < io->io_size; idx++) अणु
		अगर (request_region(addr + idx * io->regspacing,
				   io->regsize, SI_DEVICE_NAME) == शून्य) अणु
			/* Unकरो allocations */
			जबतक (idx--)
				release_region(addr + idx * io->regspacing,
					       io->regsize);
			वापस -EIO;
		पूर्ण
	पूर्ण

	io->io_cleanup = port_cleanup;

	वापस 0;
पूर्ण
