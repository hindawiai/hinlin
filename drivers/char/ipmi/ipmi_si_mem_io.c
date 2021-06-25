<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/पन.स>
#समावेश "ipmi_si.h"

अटल अचिन्हित अक्षर पूर्णांकf_mem_inb(स्थिर काष्ठा si_sm_io *io,
				  अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोb((io->addr)+(offset * io->regspacing));
पूर्ण

अटल व्योम पूर्णांकf_mem_outb(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset,
			  अचिन्हित अक्षर b)
अणु
	ग_लिखोb(b, (io->addr)+(offset * io->regspacing));
पूर्ण

अटल अचिन्हित अक्षर पूर्णांकf_mem_inw(स्थिर काष्ठा si_sm_io *io,
				  अचिन्हित पूर्णांक offset)
अणु
	वापस (पढ़ोw((io->addr)+(offset * io->regspacing)) >> io->regshअगरt)
		& 0xff;
पूर्ण

अटल व्योम पूर्णांकf_mem_outw(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset,
			  अचिन्हित अक्षर b)
अणु
	ग_लिखोb(b << io->regshअगरt, (io->addr)+(offset * io->regspacing));
पूर्ण

अटल अचिन्हित अक्षर पूर्णांकf_mem_inl(स्थिर काष्ठा si_sm_io *io,
				  अचिन्हित पूर्णांक offset)
अणु
	वापस (पढ़ोl((io->addr)+(offset * io->regspacing)) >> io->regshअगरt)
		& 0xff;
पूर्ण

अटल व्योम पूर्णांकf_mem_outl(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset,
			  अचिन्हित अक्षर b)
अणु
	ग_लिखोl(b << io->regshअगरt, (io->addr)+(offset * io->regspacing));
पूर्ण

#अगर_घोषित पढ़ोq
अटल अचिन्हित अक्षर mem_inq(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset)
अणु
	वापस (पढ़ोq((io->addr)+(offset * io->regspacing)) >> io->regshअगरt)
		& 0xff;
पूर्ण

अटल व्योम mem_outq(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset,
		     अचिन्हित अक्षर b)
अणु
	ग_लिखोq((u64)b << io->regshअगरt, (io->addr)+(offset * io->regspacing));
पूर्ण
#पूर्ण_अगर

अटल व्योम mem_region_cleanup(काष्ठा si_sm_io *io, पूर्णांक num)
अणु
	अचिन्हित दीर्घ addr = io->addr_data;
	पूर्णांक idx;

	क्रम (idx = 0; idx < num; idx++)
		release_mem_region(addr + idx * io->regspacing,
				   io->regsize);
पूर्ण

अटल व्योम mem_cleanup(काष्ठा si_sm_io *io)
अणु
	अगर (io->addr) अणु
		iounmap(io->addr);
		mem_region_cleanup(io, io->io_size);
	पूर्ण
पूर्ण

पूर्णांक ipmi_si_mem_setup(काष्ठा si_sm_io *io)
अणु
	अचिन्हित दीर्घ addr = io->addr_data;
	पूर्णांक           mapsize, idx;

	अगर (!addr)
		वापस -ENODEV;

	/*
	 * Figure out the actual पढ़ोb/पढ़ोw/पढ़ोl/etc routine to use based
	 * upon the रेजिस्टर size.
	 */
	चयन (io->regsize) अणु
	हाल 1:
		io->inputb = पूर्णांकf_mem_inb;
		io->outputb = पूर्णांकf_mem_outb;
		अवरोध;
	हाल 2:
		io->inputb = पूर्णांकf_mem_inw;
		io->outputb = पूर्णांकf_mem_outw;
		अवरोध;
	हाल 4:
		io->inputb = पूर्णांकf_mem_inl;
		io->outputb = पूर्णांकf_mem_outl;
		अवरोध;
#अगर_घोषित पढ़ोq
	हाल 8:
		io->inputb = mem_inq;
		io->outputb = mem_outq;
		अवरोध;
#पूर्ण_अगर
	शेष:
		dev_warn(io->dev, "Invalid register size: %d\n",
			 io->regsize);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Some BIOSes reserve disjoपूर्णांक memory regions in their ACPI
	 * tables.  This causes problems when trying to request the
	 * entire region.  Thereक्रमe we must request each रेजिस्टर
	 * separately.
	 */
	क्रम (idx = 0; idx < io->io_size; idx++) अणु
		अगर (request_mem_region(addr + idx * io->regspacing,
				       io->regsize, SI_DEVICE_NAME) == शून्य) अणु
			/* Unकरो allocations */
			mem_region_cleanup(io, idx);
			वापस -EIO;
		पूर्ण
	पूर्ण

	/*
	 * Calculate the total amount of memory to claim.  This is an
	 * unusual looking calculation, but it aव्योमs claiming any
	 * more memory than it has to.  It will claim everything
	 * between the first address to the end of the last full
	 * रेजिस्टर.
	 */
	mapsize = ((io->io_size * io->regspacing)
		   - (io->regspacing - io->regsize));
	io->addr = ioremap(addr, mapsize);
	अगर (io->addr == शून्य) अणु
		mem_region_cleanup(io, io->io_size);
		वापस -EIO;
	पूर्ण

	io->io_cleanup = mem_cleanup;

	वापस 0;
पूर्ण
