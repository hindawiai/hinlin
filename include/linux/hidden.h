<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * When building position independent code with GCC using the -fPIC option,
 * (or even the -fPIE one on older versions), it will assume that we are
 * building a dynamic object (either a shared library or an executable) that
 * may have symbol references that can only be resolved at load समय. For a
 * variety of reasons (ELF symbol preemption, the CoW footprपूर्णांक of the section
 * that is modअगरied by the loader), this results in all references to symbols
 * with बाह्यal linkage to go via entries in the Global Offset Table (GOT),
 * which carries असलolute addresses which need to be fixed up when the
 * executable image is loaded at an offset which is dअगरferent from its link
 * समय offset.
 *
 * Fortunately, there is a way to inक्रमm the compiler that such symbol
 * references will be satisfied at link समय rather than at load समय, by
 * giving them 'hidden' visibility.
 */

#आशय GCC visibility push(hidden)
