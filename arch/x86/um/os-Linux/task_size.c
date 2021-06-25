<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <sys/mman.h>
#समावेश <दीर्घ_लाँघ.h>

#अगर_घोषित __i386__

अटल लाँघ_बफ buf;

अटल व्योम segfault(पूर्णांक sig)
अणु
	दीर्घ_लाँघ(buf, 1);
पूर्ण

अटल पूर्णांक page_ok(अचिन्हित दीर्घ page)
अणु
	अचिन्हित दीर्घ *address = (अचिन्हित दीर्घ *) (page << UM_KERN_PAGE_SHIFT);
	अचिन्हित दीर्घ n = ~0UL;
	व्योम *mapped = शून्य;
	पूर्णांक ok = 0;

	/*
	 * First see अगर the page is पढ़ोable.  If it is, it may still
	 * be a VDSO, so we go on to see अगर it's writable.  If not
	 * then try mapping memory there.  If that fails, then we're
	 * still in the kernel area.  As a sanity check, we'll fail अगर
	 * the mmap succeeds, but gives us an address dअगरferent from
	 * what we wanted.
	 */
	अगर (बनाओ_लाँघ(buf) == 0)
		n = *address;
	अन्यथा अणु
		mapped = mmap(address, UM_KERN_PAGE_SIZE,
			      PROT_READ | PROT_WRITE,
			      MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		अगर (mapped == MAP_FAILED)
			वापस 0;
		अगर (mapped != address)
			जाओ out;
	पूर्ण

	/*
	 * Now, is it ग_लिखोable?  If so, then we're in user address
	 * space.  If not, then try mprotecting it and try the ग_लिखो
	 * again.
	 */
	अगर (बनाओ_लाँघ(buf) == 0) अणु
		*address = n;
		ok = 1;
		जाओ out;
	पूर्ण अन्यथा अगर (mprotect(address, UM_KERN_PAGE_SIZE,
			    PROT_READ | PROT_WRITE) != 0)
		जाओ out;

	अगर (बनाओ_लाँघ(buf) == 0) अणु
		*address = n;
		ok = 1;
	पूर्ण

 out:
	अगर (mapped != शून्य)
		munmap(mapped, UM_KERN_PAGE_SIZE);
	वापस ok;
पूर्ण

अचिन्हित दीर्घ os_get_top_address(व्योम)
अणु
	काष्ठा sigaction sa, old;
	अचिन्हित दीर्घ bottom = 0;
	/*
	 * A 32-bit UML on a 64-bit host माला_लो confused about the VDSO at
	 * 0xffffe000.  It is mapped, is पढ़ोable, can be reरक्षित ग_लिखोable
	 * and written.  However, exec discovers later that it can't be
	 * unmapped.  So, just set the highest address to be checked to just
	 * below it.  This might waste some address space on 4G/4G 32-bit
	 * hosts, but shouldn't hurt otherwise.
	 */
	अचिन्हित दीर्घ top = 0xffffd000 >> UM_KERN_PAGE_SHIFT;
	अचिन्हित दीर्घ test, original;

	म_लिखो("Locating the bottom of the address space ... ");
	ख_साफ(मानक_निकास);

	/*
	 * We're going to be दीर्घ_लाँघing out of the संकेत handler, so
	 * SA_DEFER needs to be set.
	 */
	sa.sa_handler = segfault;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_NODEFER;
	अगर (sigaction(संक_अंश, &sa, &old)) अणु
		लिखो_त्रुटि("os_get_top_address");
		निकास(1);
	पूर्ण

	/* Manually scan the address space, bottom-up, until we find
	 * the first valid page (or run out of them).
	 */
	क्रम (bottom = 0; bottom < top; bottom++) अणु
		अगर (page_ok(bottom))
			अवरोध;
	पूर्ण

	/* If we've got this far, we ran out of pages. */
	अगर (bottom == top) अणु
		ख_लिखो(मानक_त्रुटि, "Unable to determine bottom of address "
			"space.\n");
		निकास(1);
	पूर्ण

	म_लिखो("0x%lx\n", bottom << UM_KERN_PAGE_SHIFT);
	म_लिखो("Locating the top of the address space ... ");
	ख_साफ(मानक_निकास);

	original = bottom;

	/* This could happen with a 4G/4G split */
	अगर (page_ok(top))
		जाओ out;

	करो अणु
		test = bottom + (top - bottom) / 2;
		अगर (page_ok(test))
			bottom = test;
		अन्यथा
			top = test;
	पूर्ण जबतक (top - bottom > 1);

out:
	/* Restore the old संक_अंश handling */
	अगर (sigaction(संक_अंश, &old, शून्य)) अणु
		लिखो_त्रुटि("os_get_top_address");
		निकास(1);
	पूर्ण
	top <<= UM_KERN_PAGE_SHIFT;
	म_लिखो("0x%lx\n", top);

	वापस top;
पूर्ण

#अन्यथा

अचिन्हित दीर्घ os_get_top_address(व्योम)
अणु
	/* The old value of CONFIG_TOP_ADDR */
	वापस 0x7fc0002000;
पूर्ण

#पूर्ण_अगर
