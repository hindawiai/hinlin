<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hypervisor fileप्रणाली क्रम Linux on s390
 *
 * Diag 0C implementation
 *
 * Copyright IBM Corp. 2014
 */

#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/hypfs.h>
#समावेश "hypfs.h"

#घोषणा DBFS_D0C_HDR_VERSION 0

/*
 * Get hypfs_diag0c_entry from CPU vector and store diag0c data
 */
अटल व्योम diag0c_fn(व्योम *data)
अणु
	diag_stat_inc(DIAG_STAT_X00C);
	diag_dma_ops.diag0c(((व्योम **) data)[smp_processor_id()]);
पूर्ण

/*
 * Allocate buffer and store diag 0c data
 */
अटल व्योम *diag0c_store(अचिन्हित पूर्णांक *count)
अणु
	काष्ठा hypfs_diag0c_data *diag0c_data;
	अचिन्हित पूर्णांक cpu_count, cpu, i;
	व्योम **cpu_vec;

	get_online_cpus();
	cpu_count = num_online_cpus();
	cpu_vec = kदो_स्मृति_array(num_possible_cpus(), माप(*cpu_vec),
				GFP_KERNEL);
	अगर (!cpu_vec)
		जाओ fail_put_online_cpus;
	/* Note: Diag 0c needs 8 byte alignment and real storage */
	diag0c_data = kzalloc(काष्ठा_size(diag0c_data, entry, cpu_count),
			      GFP_KERNEL | GFP_DMA);
	अगर (!diag0c_data)
		जाओ fail_kमुक्त_cpu_vec;
	i = 0;
	/* Fill CPU vector क्रम each online CPU */
	क्रम_each_online_cpu(cpu) अणु
		diag0c_data->entry[i].cpu = cpu;
		cpu_vec[cpu] = &diag0c_data->entry[i++];
	पूर्ण
	/* Collect data all CPUs */
	on_each_cpu(diag0c_fn, cpu_vec, 1);
	*count = cpu_count;
	kमुक्त(cpu_vec);
	put_online_cpus();
	वापस diag0c_data;

fail_kमुक्त_cpu_vec:
	kमुक्त(cpu_vec);
fail_put_online_cpus:
	put_online_cpus();
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * Hypfs DBFS callback: Free diag 0c data
 */
अटल व्योम dbfs_diag0c_मुक्त(स्थिर व्योम *data)
अणु
	kमुक्त(data);
पूर्ण

/*
 * Hypfs DBFS callback: Create diag 0c data
 */
अटल पूर्णांक dbfs_diag0c_create(व्योम **data, व्योम **data_मुक्त_ptr, माप_प्रकार *size)
अणु
	काष्ठा hypfs_diag0c_data *diag0c_data;
	अचिन्हित पूर्णांक count;

	diag0c_data = diag0c_store(&count);
	अगर (IS_ERR(diag0c_data))
		वापस PTR_ERR(diag0c_data);
	स_रखो(&diag0c_data->hdr, 0, माप(diag0c_data->hdr));
	store_tod_घड़ी_ext((जोड़ tod_घड़ी *)diag0c_data->hdr.tod_ext);
	diag0c_data->hdr.len = count * माप(काष्ठा hypfs_diag0c_entry);
	diag0c_data->hdr.version = DBFS_D0C_HDR_VERSION;
	diag0c_data->hdr.count = count;
	*data = diag0c_data;
	*data_मुक्त_ptr = diag0c_data;
	*size = diag0c_data->hdr.len + माप(काष्ठा hypfs_diag0c_hdr);
	वापस 0;
पूर्ण

/*
 * Hypfs DBFS file काष्ठाure
 */
अटल काष्ठा hypfs_dbfs_file dbfs_file_0c = अणु
	.name		= "diag_0c",
	.data_create	= dbfs_diag0c_create,
	.data_मुक्त	= dbfs_diag0c_मुक्त,
पूर्ण;

/*
 * Initialize diag 0c पूर्णांकerface क्रम z/VM
 */
पूर्णांक __init hypfs_diag0c_init(व्योम)
अणु
	अगर (!MACHINE_IS_VM)
		वापस 0;
	hypfs_dbfs_create_file(&dbfs_file_0c);
	वापस 0;
पूर्ण

/*
 * Shutकरोwn diag 0c पूर्णांकerface क्रम z/VM
 */
व्योम hypfs_diag0c_निकास(व्योम)
अणु
	अगर (!MACHINE_IS_VM)
		वापस;
	hypfs_dbfs_हटाओ_file(&dbfs_file_0c);
पूर्ण
