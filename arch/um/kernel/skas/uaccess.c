<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/err.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/page.h>
#समावेश <kern_util.h>
#समावेश <os.h>

pte_t *virt_to_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	अगर (mm == शून्य)
		वापस शून्य;

	pgd = pgd_offset(mm, addr);
	अगर (!pgd_present(*pgd))
		वापस शून्य;

	p4d = p4d_offset(pgd, addr);
	अगर (!p4d_present(*p4d))
		वापस शून्य;

	pud = pud_offset(p4d, addr);
	अगर (!pud_present(*pud))
		वापस शून्य;

	pmd = pmd_offset(pud, addr);
	अगर (!pmd_present(*pmd))
		वापस शून्य;

	वापस pte_offset_kernel(pmd, addr);
पूर्ण

अटल pte_t *maybe_map(अचिन्हित दीर्घ virt, पूर्णांक is_ग_लिखो)
अणु
	pte_t *pte = virt_to_pte(current->mm, virt);
	पूर्णांक err, dummy_code;

	अगर ((pte == शून्य) || !pte_present(*pte) ||
	    (is_ग_लिखो && !pte_ग_लिखो(*pte))) अणु
		err = handle_page_fault(virt, 0, is_ग_लिखो, 1, &dummy_code);
		अगर (err)
			वापस शून्य;
		pte = virt_to_pte(current->mm, virt);
	पूर्ण
	अगर (!pte_present(*pte))
		pte = शून्य;

	वापस pte;
पूर्ण

अटल पूर्णांक करो_op_one_page(अचिन्हित दीर्घ addr, पूर्णांक len, पूर्णांक is_ग_लिखो,
		 पूर्णांक (*op)(अचिन्हित दीर्घ addr, पूर्णांक len, व्योम *arg), व्योम *arg)
अणु
	काष्ठा page *page;
	pte_t *pte;
	पूर्णांक n;

	pte = maybe_map(addr, is_ग_लिखो);
	अगर (pte == शून्य)
		वापस -1;

	page = pte_page(*pte);
#अगर_घोषित CONFIG_64BIT
	pagefault_disable();
	addr = (अचिन्हित दीर्घ) page_address(page) +
		(addr & ~PAGE_MASK);
#अन्यथा
	addr = (अचिन्हित दीर्घ) kmap_atomic(page) +
		(addr & ~PAGE_MASK);
#पूर्ण_अगर
	n = (*op)(addr, len, arg);

#अगर_घोषित CONFIG_64BIT
	pagefault_enable();
#अन्यथा
	kunmap_atomic((व्योम *)addr);
#पूर्ण_अगर

	वापस n;
पूर्ण

अटल दीर्घ buffer_op(अचिन्हित दीर्घ addr, पूर्णांक len, पूर्णांक is_ग_लिखो,
		      पूर्णांक (*op)(अचिन्हित दीर्घ, पूर्णांक, व्योम *), व्योम *arg)
अणु
	दीर्घ size, reमुख्य, n;

	size = min(PAGE_ALIGN(addr) - addr, (अचिन्हित दीर्घ) len);
	reमुख्य = len;

	n = करो_op_one_page(addr, size, is_ग_लिखो, op, arg);
	अगर (n != 0) अणु
		reमुख्य = (n < 0 ? reमुख्य : 0);
		जाओ out;
	पूर्ण

	addr += size;
	reमुख्य -= size;
	अगर (reमुख्य == 0)
		जाओ out;

	जबतक (addr < ((addr + reमुख्य) & PAGE_MASK)) अणु
		n = करो_op_one_page(addr, PAGE_SIZE, is_ग_लिखो, op, arg);
		अगर (n != 0) अणु
			reमुख्य = (n < 0 ? reमुख्य : 0);
			जाओ out;
		पूर्ण

		addr += PAGE_SIZE;
		reमुख्य -= PAGE_SIZE;
	पूर्ण
	अगर (reमुख्य == 0)
		जाओ out;

	n = करो_op_one_page(addr, reमुख्य, is_ग_लिखो, op, arg);
	अगर (n != 0) अणु
		reमुख्य = (n < 0 ? reमुख्य : 0);
		जाओ out;
	पूर्ण

	वापस 0;
 out:
	वापस reमुख्य;
पूर्ण

अटल पूर्णांक copy_chunk_from_user(अचिन्हित दीर्घ from, पूर्णांक len, व्योम *arg)
अणु
	अचिन्हित दीर्घ *to_ptr = arg, to = *to_ptr;

	स_नकल((व्योम *) to, (व्योम *) from, len);
	*to_ptr += len;
	वापस 0;
पूर्ण

अचिन्हित दीर्घ raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अगर (uaccess_kernel()) अणु
		स_नकल(to, (__क्रमce व्योम*)from, n);
		वापस 0;
	पूर्ण

	वापस buffer_op((अचिन्हित दीर्घ) from, n, 0, copy_chunk_from_user, &to);
पूर्ण
EXPORT_SYMBOL(raw_copy_from_user);

अटल पूर्णांक copy_chunk_to_user(अचिन्हित दीर्घ to, पूर्णांक len, व्योम *arg)
अणु
	अचिन्हित दीर्घ *from_ptr = arg, from = *from_ptr;

	स_नकल((व्योम *) to, (व्योम *) from, len);
	*from_ptr += len;
	वापस 0;
पूर्ण

अचिन्हित दीर्घ raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	अगर (uaccess_kernel()) अणु
		स_नकल((__क्रमce व्योम *) to, from, n);
		वापस 0;
	पूर्ण

	वापस buffer_op((अचिन्हित दीर्घ) to, n, 1, copy_chunk_to_user, &from);
पूर्ण
EXPORT_SYMBOL(raw_copy_to_user);

अटल पूर्णांक म_नकलन_chunk_from_user(अचिन्हित दीर्घ from, पूर्णांक len, व्योम *arg)
अणु
	अक्षर **to_ptr = arg, *to = *to_ptr;
	पूर्णांक n;

	म_नकलन(to, (व्योम *) from, len);
	n = strnlen(to, len);
	*to_ptr += n;

	अगर (n < len)
	        वापस 1;
	वापस 0;
पूर्ण

दीर्घ __म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count)
अणु
	दीर्घ n;
	अक्षर *ptr = dst;

	अगर (uaccess_kernel()) अणु
		म_नकलन(dst, (__क्रमce व्योम *) src, count);
		वापस strnlen(dst, count);
	पूर्ण

	n = buffer_op((अचिन्हित दीर्घ) src, count, 0, म_नकलन_chunk_from_user,
		      &ptr);
	अगर (n != 0)
		वापस -EFAULT;
	वापस strnlen(dst, count);
पूर्ण
EXPORT_SYMBOL(__म_नकलन_from_user);

अटल पूर्णांक clear_chunk(अचिन्हित दीर्घ addr, पूर्णांक len, व्योम *unused)
अणु
	स_रखो((व्योम *) addr, 0, len);
	वापस 0;
पूर्ण

अचिन्हित दीर्घ __clear_user(व्योम __user *mem, अचिन्हित दीर्घ len)
अणु
	अगर (uaccess_kernel()) अणु
		स_रखो((__क्रमce व्योम*)mem, 0, len);
		वापस 0;
	पूर्ण

	वापस buffer_op((अचिन्हित दीर्घ) mem, len, 1, clear_chunk, शून्य);
पूर्ण
EXPORT_SYMBOL(__clear_user);

अटल पूर्णांक strnlen_chunk(अचिन्हित दीर्घ str, पूर्णांक len, व्योम *arg)
अणु
	पूर्णांक *len_ptr = arg, n;

	n = strnlen((व्योम *) str, len);
	*len_ptr += n;

	अगर (n < len)
		वापस 1;
	वापस 0;
पूर्ण

दीर्घ __strnlen_user(स्थिर व्योम __user *str, दीर्घ len)
अणु
	पूर्णांक count = 0, n;

	अगर (uaccess_kernel())
		वापस strnlen((__क्रमce अक्षर*)str, len) + 1;

	n = buffer_op((अचिन्हित दीर्घ) str, len, 0, strnlen_chunk, &count);
	अगर (n == 0)
		वापस count + 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__strnlen_user);
