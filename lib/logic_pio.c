<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 HiSilicon Limited, All Rights Reserved.
 * Author: Gabriele Paoloni <gabriele.paoloni@huawei.com>
 * Author: Zhichang Yuan <yuanzhichang@hisilicon.com>
 * Author: John Garry <john.garry@huawei.com>
 */

#घोषणा pr_fmt(fmt)	"LOGIC PIO: " fmt

#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/logic_pपन.स>
#समावेश <linux/mm.h>
#समावेश <linux/rculist.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>

/* The unique hardware address list */
अटल LIST_HEAD(io_range_list);
अटल DEFINE_MUTEX(io_range_mutex);

/* Consider a kernel general helper क्रम this */
#घोषणा in_range(b, first, len)        ((b) >= (first) && (b) < (first) + (len))

/**
 * logic_pio_रेजिस्टर_range - रेजिस्टर logical PIO range क्रम a host
 * @new_range: poपूर्णांकer to the IO range to be रेजिस्टरed.
 *
 * Returns 0 on success, the error code in हाल of failure.
 * If the range alपढ़ोy exists, -EEXIST will be वापसed, which should be
 * considered a success.
 *
 * Register a new IO range node in the IO range list.
 */
पूर्णांक logic_pio_रेजिस्टर_range(काष्ठा logic_pio_hwaddr *new_range)
अणु
	काष्ठा logic_pio_hwaddr *range;
	resource_माप_प्रकार start;
	resource_माप_प्रकार end;
	resource_माप_प्रकार mmio_end = 0;
	resource_माप_प्रकार iio_sz = MMIO_UPPER_LIMIT;
	पूर्णांक ret = 0;

	अगर (!new_range || !new_range->fwnode || !new_range->size ||
	    (new_range->flags == LOGIC_PIO_INसूचीECT && !new_range->ops))
		वापस -EINVAL;

	start = new_range->hw_start;
	end = new_range->hw_start + new_range->size;

	mutex_lock(&io_range_mutex);
	list_क्रम_each_entry(range, &io_range_list, list) अणु
		अगर (range->fwnode == new_range->fwnode) अणु
			/* range alपढ़ोy there */
			ret = -EEXIST;
			जाओ end_रेजिस्टर;
		पूर्ण
		अगर (range->flags == LOGIC_PIO_CPU_MMIO &&
		    new_range->flags == LOGIC_PIO_CPU_MMIO) अणु
			/* क्रम MMIO ranges we need to check क्रम overlap */
			अगर (start >= range->hw_start + range->size ||
			    end < range->hw_start) अणु
				mmio_end = range->io_start + range->size;
			पूर्ण अन्यथा अणु
				ret = -EFAULT;
				जाओ end_रेजिस्टर;
			पूर्ण
		पूर्ण अन्यथा अगर (range->flags == LOGIC_PIO_INसूचीECT &&
			   new_range->flags == LOGIC_PIO_INसूचीECT) अणु
			iio_sz += range->size;
		पूर्ण
	पूर्ण

	/* range not रेजिस्टरed yet, check क्रम available space */
	अगर (new_range->flags == LOGIC_PIO_CPU_MMIO) अणु
		अगर (mmio_end + new_range->size - 1 > MMIO_UPPER_LIMIT) अणु
			/* अगर it's too big check अगर 64K space can be reserved */
			अगर (mmio_end + SZ_64K - 1 > MMIO_UPPER_LIMIT) अणु
				ret = -E2BIG;
				जाओ end_रेजिस्टर;
			पूर्ण
			new_range->size = SZ_64K;
			pr_warn("Requested IO range too big, new size set to 64K\n");
		पूर्ण
		new_range->io_start = mmio_end;
	पूर्ण अन्यथा अगर (new_range->flags == LOGIC_PIO_INसूचीECT) अणु
		अगर (iio_sz + new_range->size - 1 > IO_SPACE_LIMIT) अणु
			ret = -E2BIG;
			जाओ end_रेजिस्टर;
		पूर्ण
		new_range->io_start = iio_sz;
	पूर्ण अन्यथा अणु
		/* invalid flag */
		ret = -EINVAL;
		जाओ end_रेजिस्टर;
	पूर्ण

	list_add_tail_rcu(&new_range->list, &io_range_list);

end_रेजिस्टर:
	mutex_unlock(&io_range_mutex);
	वापस ret;
पूर्ण

/**
 * logic_pio_unरेजिस्टर_range - unरेजिस्टर a logical PIO range क्रम a host
 * @range: poपूर्णांकer to the IO range which has been alपढ़ोy रेजिस्टरed.
 *
 * Unरेजिस्टर a previously-रेजिस्टरed IO range node.
 */
व्योम logic_pio_unरेजिस्टर_range(काष्ठा logic_pio_hwaddr *range)
अणु
	mutex_lock(&io_range_mutex);
	list_del_rcu(&range->list);
	mutex_unlock(&io_range_mutex);
	synchronize_rcu();
पूर्ण

/**
 * find_io_range_by_fwnode - find logical PIO range क्रम given FW node
 * @fwnode: FW node handle associated with logical PIO range
 *
 * Returns poपूर्णांकer to node on success, शून्य otherwise.
 *
 * Traverse the io_range_list to find the रेजिस्टरed node क्रम @fwnode.
 */
काष्ठा logic_pio_hwaddr *find_io_range_by_fwnode(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा logic_pio_hwaddr *range, *found_range = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(range, &io_range_list, list) अणु
		अगर (range->fwnode == fwnode) अणु
			found_range = range;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस found_range;
पूर्ण

/* Return a रेजिस्टरed range given an input PIO token */
अटल काष्ठा logic_pio_hwaddr *find_io_range(अचिन्हित दीर्घ pio)
अणु
	काष्ठा logic_pio_hwaddr *range, *found_range = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(range, &io_range_list, list) अणु
		अगर (in_range(pio, range->io_start, range->size)) अणु
			found_range = range;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!found_range)
		pr_err("PIO entry token 0x%lx invalid\n", pio);

	वापस found_range;
पूर्ण

/**
 * logic_pio_to_hwaddr - translate logical PIO to HW address
 * @pio: logical PIO value
 *
 * Returns HW address अगर valid, ~0 otherwise.
 *
 * Translate the input logical PIO to the corresponding hardware address.
 * The input PIO should be unique in the whole logical PIO space.
 */
resource_माप_प्रकार logic_pio_to_hwaddr(अचिन्हित दीर्घ pio)
अणु
	काष्ठा logic_pio_hwaddr *range;

	range = find_io_range(pio);
	अगर (range)
		वापस range->hw_start + pio - range->io_start;

	वापस (resource_माप_प्रकार)~0;
पूर्ण

/**
 * logic_pio_trans_hwaddr - translate HW address to logical PIO
 * @fwnode: FW node reference क्रम the host
 * @addr: Host-relative HW address
 * @size: size to translate
 *
 * Returns Logical PIO value अगर successful, ~0UL otherwise
 */
अचिन्हित दीर्घ logic_pio_trans_hwaddr(काष्ठा fwnode_handle *fwnode,
				     resource_माप_प्रकार addr, resource_माप_प्रकार size)
अणु
	काष्ठा logic_pio_hwaddr *range;

	range = find_io_range_by_fwnode(fwnode);
	अगर (!range || range->flags == LOGIC_PIO_CPU_MMIO) अणु
		pr_err("IO range not found or invalid\n");
		वापस ~0UL;
	पूर्ण
	अगर (range->size < size) अणु
		pr_err("resource size %pa cannot fit in IO range size %pa\n",
		       &size, &range->size);
		वापस ~0UL;
	पूर्ण
	वापस addr - range->hw_start + range->io_start;
पूर्ण

अचिन्हित दीर्घ logic_pio_trans_cpuaddr(resource_माप_प्रकार addr)
अणु
	काष्ठा logic_pio_hwaddr *range;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(range, &io_range_list, list) अणु
		अगर (range->flags != LOGIC_PIO_CPU_MMIO)
			जारी;
		अगर (in_range(addr, range->hw_start, range->size)) अणु
			अचिन्हित दीर्घ cpuaddr;

			cpuaddr = addr - range->hw_start + range->io_start;

			rcu_पढ़ो_unlock();
			वापस cpuaddr;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	pr_err("addr %pa not registered in io_range_list\n", &addr);

	वापस ~0UL;
पूर्ण

#अगर defined(CONFIG_INसूचीECT_PIO) && defined(PCI_IOBASE)
#घोषणा BUILD_LOGIC_IO(bwl, type)					\
type logic_in##bwl(अचिन्हित दीर्घ addr)					\
अणु									\
	type ret = (type)~0;						\
									\
	अगर (addr < MMIO_UPPER_LIMIT) अणु					\
		ret = _in##bwl(addr);					\
	पूर्ण अन्यथा अगर (addr >= MMIO_UPPER_LIMIT && addr < IO_SPACE_LIMIT) अणु \
		काष्ठा logic_pio_hwaddr *entry = find_io_range(addr);	\
									\
		अगर (entry)						\
			ret = entry->ops->in(entry->hostdata,		\
					addr, माप(type));		\
		अन्यथा							\
			WARN_ON_ONCE(1);				\
	पूर्ण								\
	वापस ret;							\
पूर्ण									\
									\
व्योम logic_out##bwl(type value, अचिन्हित दीर्घ addr)			\
अणु									\
	अगर (addr < MMIO_UPPER_LIMIT) अणु					\
		_out##bwl(value, addr);				\
	पूर्ण अन्यथा अगर (addr >= MMIO_UPPER_LIMIT && addr < IO_SPACE_LIMIT) अणु	\
		काष्ठा logic_pio_hwaddr *entry = find_io_range(addr);	\
									\
		अगर (entry)						\
			entry->ops->out(entry->hostdata,		\
					addr, value, माप(type));	\
		अन्यथा							\
			WARN_ON_ONCE(1);				\
	पूर्ण								\
पूर्ण									\
									\
व्योम logic_ins##bwl(अचिन्हित दीर्घ addr, व्योम *buffer,			\
		    अचिन्हित पूर्णांक count)					\
अणु									\
	अगर (addr < MMIO_UPPER_LIMIT) अणु					\
		पढ़ोs##bwl(PCI_IOBASE + addr, buffer, count);		\
	पूर्ण अन्यथा अगर (addr >= MMIO_UPPER_LIMIT && addr < IO_SPACE_LIMIT) अणु	\
		काष्ठा logic_pio_hwaddr *entry = find_io_range(addr);	\
									\
		अगर (entry)						\
			entry->ops->ins(entry->hostdata,		\
				addr, buffer, माप(type), count);	\
		अन्यथा							\
			WARN_ON_ONCE(1);				\
	पूर्ण								\
									\
पूर्ण									\
									\
व्योम logic_outs##bwl(अचिन्हित दीर्घ addr, स्थिर व्योम *buffer,		\
		     अचिन्हित पूर्णांक count)				\
अणु									\
	अगर (addr < MMIO_UPPER_LIMIT) अणु					\
		ग_लिखोs##bwl(PCI_IOBASE + addr, buffer, count);		\
	पूर्ण अन्यथा अगर (addr >= MMIO_UPPER_LIMIT && addr < IO_SPACE_LIMIT) अणु	\
		काष्ठा logic_pio_hwaddr *entry = find_io_range(addr);	\
									\
		अगर (entry)						\
			entry->ops->outs(entry->hostdata,		\
				addr, buffer, माप(type), count);	\
		अन्यथा							\
			WARN_ON_ONCE(1);				\
	पूर्ण								\
पूर्ण

BUILD_LOGIC_IO(b, u8)
EXPORT_SYMBOL(logic_inb);
EXPORT_SYMBOL(logic_insb);
EXPORT_SYMBOL(logic_outb);
EXPORT_SYMBOL(logic_outsb);

BUILD_LOGIC_IO(w, u16)
EXPORT_SYMBOL(logic_inw);
EXPORT_SYMBOL(logic_insw);
EXPORT_SYMBOL(logic_outw);
EXPORT_SYMBOL(logic_outsw);

BUILD_LOGIC_IO(l, u32)
EXPORT_SYMBOL(logic_inl);
EXPORT_SYMBOL(logic_insl);
EXPORT_SYMBOL(logic_outl);
EXPORT_SYMBOL(logic_outsl);

#पूर्ण_अगर /* CONFIG_INसूचीECT_PIO && PCI_IOBASE */
