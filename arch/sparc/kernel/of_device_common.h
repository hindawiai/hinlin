<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _OF_DEVICE_COMMON_H
#घोषणा _OF_DEVICE_COMMON_H

अटल अंतरभूत u64 of_पढ़ो_addr(स्थिर u32 *cell, पूर्णांक size)
अणु
	u64 r = 0;
	जबतक (size--)
		r = (r << 32) | *(cell++);
	वापस r;
पूर्ण

व्योम of_bus_शेष_count_cells(काष्ठा device_node *dev, पूर्णांक *addrc,
				पूर्णांक *sizec);
पूर्णांक of_out_of_range(स्थिर u32 *addr, स्थिर u32 *base,
		    स्थिर u32 *size, पूर्णांक na, पूर्णांक ns);
पूर्णांक of_bus_शेष_map(u32 *addr, स्थिर u32 *range, पूर्णांक na, पूर्णांक ns, पूर्णांक pna);
अचिन्हित दीर्घ of_bus_शेष_get_flags(स्थिर u32 *addr, अचिन्हित दीर्घ flags);

पूर्णांक of_bus_sbus_match(काष्ठा device_node *np);
व्योम of_bus_sbus_count_cells(काष्ठा device_node *child, पूर्णांक *addrc, पूर्णांक *sizec);

/* Max address size we deal with */
#घोषणा OF_MAX_ADDR_CELLS	4

काष्ठा of_bus अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*addr_prop_name;
	पूर्णांक		(*match)(काष्ठा device_node *parent);
	व्योम		(*count_cells)(काष्ठा device_node *child,
				       पूर्णांक *addrc, पूर्णांक *sizec);
	पूर्णांक		(*map)(u32 *addr, स्थिर u32 *range,
			       पूर्णांक na, पूर्णांक ns, पूर्णांक pna);
	अचिन्हित दीर्घ	(*get_flags)(स्थिर u32 *addr, अचिन्हित दीर्घ);
पूर्ण;

#पूर्ण_अगर /* _OF_DEVICE_COMMON_H */
