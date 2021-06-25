<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  c 2001 PPC 64 Team, IBM Corp
 *
 * /dev/nvram driver क्रम PPC64
 */


#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/nvram.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>

/* Max bytes to पढ़ो/ग_लिखो in one go */
#घोषणा NVRW_CNT 0x20

अटल अचिन्हित पूर्णांक nvram_size;
अटल पूर्णांक nvram_fetch, nvram_store;
अटल अक्षर nvram_buf[NVRW_CNT];	/* assume this is in the first 4GB */
अटल DEFINE_SPINLOCK(nvram_lock);

/* See clobbering_unपढ़ो_rtas_event() */
#घोषणा NVRAM_RTAS_READ_TIMEOUT 5		/* seconds */
अटल समय64_t last_unपढ़ो_rtas_event;		/* बारtamp */

#अगर_घोषित CONFIG_PSTORE
समय64_t last_rtas_event;
#पूर्ण_अगर

अटल sमाप_प्रकार pSeries_nvram_पढ़ो(अक्षर *buf, माप_प्रकार count, loff_t *index)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ len;
	पूर्णांक करोne;
	अचिन्हित दीर्घ flags;
	अक्षर *p = buf;


	अगर (nvram_size == 0 || nvram_fetch == RTAS_UNKNOWN_SERVICE)
		वापस -ENODEV;

	अगर (*index >= nvram_size)
		वापस 0;

	i = *index;
	अगर (i + count > nvram_size)
		count = nvram_size - i;

	spin_lock_irqsave(&nvram_lock, flags);

	क्रम (; count != 0; count -= len) अणु
		len = count;
		अगर (len > NVRW_CNT)
			len = NVRW_CNT;
		
		अगर ((rtas_call(nvram_fetch, 3, 2, &करोne, i, __pa(nvram_buf),
			       len) != 0) || len != करोne) अणु
			spin_unlock_irqrestore(&nvram_lock, flags);
			वापस -EIO;
		पूर्ण
		
		स_नकल(p, nvram_buf, len);

		p += len;
		i += len;
	पूर्ण

	spin_unlock_irqrestore(&nvram_lock, flags);
	
	*index = i;
	वापस p - buf;
पूर्ण

अटल sमाप_प्रकार pSeries_nvram_ग_लिखो(अक्षर *buf, माप_प्रकार count, loff_t *index)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ len;
	पूर्णांक करोne;
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *p = buf;

	अगर (nvram_size == 0 || nvram_store == RTAS_UNKNOWN_SERVICE)
		वापस -ENODEV;

	अगर (*index >= nvram_size)
		वापस 0;

	i = *index;
	अगर (i + count > nvram_size)
		count = nvram_size - i;

	spin_lock_irqsave(&nvram_lock, flags);

	क्रम (; count != 0; count -= len) अणु
		len = count;
		अगर (len > NVRW_CNT)
			len = NVRW_CNT;

		स_नकल(nvram_buf, p, len);

		अगर ((rtas_call(nvram_store, 3, 2, &करोne, i, __pa(nvram_buf),
			       len) != 0) || len != करोne) अणु
			spin_unlock_irqrestore(&nvram_lock, flags);
			वापस -EIO;
		पूर्ण
		
		p += len;
		i += len;
	पूर्ण
	spin_unlock_irqrestore(&nvram_lock, flags);
	
	*index = i;
	वापस p - buf;
पूर्ण

अटल sमाप_प्रकार pSeries_nvram_get_size(व्योम)
अणु
	वापस nvram_size ? nvram_size : -ENODEV;
पूर्ण

/* nvram_ग_लिखो_error_log
 *
 * We need to buffer the error logs पूर्णांकo nvram to ensure that we have
 * the failure inक्रमmation to decode.
 */
पूर्णांक nvram_ग_लिखो_error_log(अक्षर * buff, पूर्णांक length,
                          अचिन्हित पूर्णांक err_type, अचिन्हित पूर्णांक error_log_cnt)
अणु
	पूर्णांक rc = nvram_ग_लिखो_os_partition(&rtas_log_partition, buff, length,
						err_type, error_log_cnt);
	अगर (!rc) अणु
		last_unपढ़ो_rtas_event = kसमय_get_real_seconds();
#अगर_घोषित CONFIG_PSTORE
		last_rtas_event = kसमय_get_real_seconds();
#पूर्ण_अगर
	पूर्ण

	वापस rc;
पूर्ण

/* nvram_पढ़ो_error_log
 *
 * Reads nvram क्रम error log क्रम at most 'length'
 */
पूर्णांक nvram_पढ़ो_error_log(अक्षर *buff, पूर्णांक length,
			अचिन्हित पूर्णांक *err_type, अचिन्हित पूर्णांक *error_log_cnt)
अणु
	वापस nvram_पढ़ो_partition(&rtas_log_partition, buff, length,
						err_type, error_log_cnt);
पूर्ण

/* This करोesn't actually zero anything, but it sets the event_logged
 * word to tell that this event is safely in syslog.
 */
पूर्णांक nvram_clear_error_log(व्योम)
अणु
	loff_t पंचांगp_index;
	पूर्णांक clear_word = ERR_FLAG_ALREADY_LOGGED;
	पूर्णांक rc;

	अगर (rtas_log_partition.index == -1)
		वापस -1;

	पंचांगp_index = rtas_log_partition.index;
	
	rc = ppc_md.nvram_ग_लिखो((अक्षर *)&clear_word, माप(पूर्णांक), &पंचांगp_index);
	अगर (rc <= 0) अणु
		prपूर्णांकk(KERN_ERR "nvram_clear_error_log: Failed nvram_write (%d)\n", rc);
		वापस rc;
	पूर्ण
	last_unपढ़ो_rtas_event = 0;

	वापस 0;
पूर्ण

/*
 * Are we using the ibm,rtas-log क्रम oops/panic reports?  And अगर so,
 * would logging this oops/panic overग_लिखो an RTAS event that rtas_errd
 * hasn't had a chance to पढ़ो and process?  Return 1 अगर so, अन्यथा 0.
 *
 * We assume that अगर rtas_errd hasn't पढ़ो the RTAS event in
 * NVRAM_RTAS_READ_TIMEOUT seconds, it's probably not going to.
 */
पूर्णांक clobbering_unपढ़ो_rtas_event(व्योम)
अणु
	वापस (oops_log_partition.index == rtas_log_partition.index
		&& last_unपढ़ो_rtas_event
		&& kसमय_get_real_seconds() - last_unपढ़ो_rtas_event <=
						NVRAM_RTAS_READ_TIMEOUT);
पूर्ण

अटल पूर्णांक __init pseries_nvram_init_log_partitions(व्योम)
अणु
	पूर्णांक rc;

	/* Scan nvram क्रम partitions */
	nvram_scan_partitions();

	rc = nvram_init_os_partition(&rtas_log_partition);
	nvram_init_oops_partition(rc == 0);
	वापस 0;
पूर्ण
machine_arch_initcall(pseries, pseries_nvram_init_log_partitions);

पूर्णांक __init pSeries_nvram_init(व्योम)
अणु
	काष्ठा device_node *nvram;
	स्थिर __be32 *nbytes_p;
	अचिन्हित पूर्णांक proplen;

	nvram = of_find_node_by_type(शून्य, "nvram");
	अगर (nvram == शून्य)
		वापस -ENODEV;

	nbytes_p = of_get_property(nvram, "#bytes", &proplen);
	अगर (nbytes_p == शून्य || proplen != माप(अचिन्हित पूर्णांक)) अणु
		of_node_put(nvram);
		वापस -EIO;
	पूर्ण

	nvram_size = be32_to_cpup(nbytes_p);

	nvram_fetch = rtas_token("nvram-fetch");
	nvram_store = rtas_token("nvram-store");
	prपूर्णांकk(KERN_INFO "PPC64 nvram contains %d bytes\n", nvram_size);
	of_node_put(nvram);

	ppc_md.nvram_पढ़ो	= pSeries_nvram_पढ़ो;
	ppc_md.nvram_ग_लिखो	= pSeries_nvram_ग_लिखो;
	ppc_md.nvram_size	= pSeries_nvram_get_size;

	वापस 0;
पूर्ण

