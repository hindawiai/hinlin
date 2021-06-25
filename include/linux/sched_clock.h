<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * sched_घड़ी.h: support क्रम extending counters to full 64-bit ns counter
 */
#अगर_अघोषित LINUX_SCHED_CLOCK
#घोषणा LINUX_SCHED_CLOCK

#अगर_घोषित CONFIG_GENERIC_SCHED_CLOCK
/**
 * काष्ठा घड़ी_पढ़ो_data - data required to पढ़ो from sched_घड़ी()
 *
 * @epoch_ns:		sched_घड़ी() value at last update
 * @epoch_cyc:		Clock cycle value at last update.
 * @sched_घड़ी_mask:   Biपंचांगask क्रम two's complement subtraction of non 64bit
 *			घड़ीs.
 * @पढ़ो_sched_घड़ी:	Current घड़ी source (or dummy source when suspended).
 * @mult:		Multipler क्रम scaled math conversion.
 * @shअगरt:		Shअगरt value क्रम scaled math conversion.
 *
 * Care must be taken when updating this काष्ठाure; it is पढ़ो by
 * some very hot code paths. It occupies <=40 bytes and, when combined
 * with the seqcount used to synchronize access, comक्रमtably fits पूर्णांकo
 * a 64 byte cache line.
 */
काष्ठा घड़ी_पढ़ो_data अणु
	u64 epoch_ns;
	u64 epoch_cyc;
	u64 sched_घड़ी_mask;
	u64 (*पढ़ो_sched_घड़ी)(व्योम);
	u32 mult;
	u32 shअगरt;
पूर्ण;

बाह्य काष्ठा घड़ी_पढ़ो_data *sched_घड़ी_पढ़ो_begin(अचिन्हित पूर्णांक *seq);
बाह्य पूर्णांक sched_घड़ी_पढ़ो_retry(अचिन्हित पूर्णांक seq);

बाह्य व्योम generic_sched_घड़ी_init(व्योम);

बाह्य व्योम sched_घड़ी_रेजिस्टर(u64 (*पढ़ो)(व्योम), पूर्णांक bits,
				 अचिन्हित दीर्घ rate);
#अन्यथा
अटल अंतरभूत व्योम generic_sched_घड़ी_init(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम sched_घड़ी_रेजिस्टर(u64 (*पढ़ो)(व्योम), पूर्णांक bits,
					अचिन्हित दीर्घ rate)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
