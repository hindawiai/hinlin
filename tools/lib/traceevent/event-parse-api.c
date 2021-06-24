<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009, 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */

#समावेश "event-parse.h"
#समावेश "event-parse-local.h"
#समावेश "event-utils.h"

/**
 * tep_get_event - वापसs the event with the given index
 * @tep: a handle to the tep_handle
 * @index: index of the requested event, in the range 0 .. nr_events
 *
 * This वापसs poपूर्णांकer to the element of the events array with the given index
 * If @tep is शून्य, or @index is not in the range 0 .. nr_events, शून्य is वापसed.
 */
काष्ठा tep_event *tep_get_event(काष्ठा tep_handle *tep, पूर्णांक index)
अणु
	अगर (tep && tep->events && index < tep->nr_events)
		वापस tep->events[index];

	वापस शून्य;
पूर्ण

/**
 * tep_get_first_event - वापसs the first event in the events array
 * @tep: a handle to the tep_handle
 *
 * This वापसs poपूर्णांकer to the first element of the events array
 * If @tep is शून्य, शून्य is वापसed.
 */
काष्ठा tep_event *tep_get_first_event(काष्ठा tep_handle *tep)
अणु
	वापस tep_get_event(tep, 0);
पूर्ण

/**
 * tep_get_events_count - get the number of defined events
 * @tep: a handle to the tep_handle
 *
 * This वापसs number of elements in event array
 * If @tep is शून्य, 0 is वापसed.
 */
पूर्णांक tep_get_events_count(काष्ठा tep_handle *tep)
अणु
	अगर (tep)
		वापस tep->nr_events;
	वापस 0;
पूर्ण

/**
 * tep_set_flag - set event parser flag
 * @tep: a handle to the tep_handle
 * @flag: flag, or combination of flags to be set
 * can be any combination from क्रमागत tep_flag
 *
 * This sets a flag or combination of flags from क्रमागत tep_flag
 */
व्योम tep_set_flag(काष्ठा tep_handle *tep, पूर्णांक flag)
अणु
	अगर (tep)
		tep->flags |= flag;
पूर्ण

/**
 * tep_clear_flag - clear event parser flag
 * @tep: a handle to the tep_handle
 * @flag: flag to be cleared
 *
 * This clears a tep flag
 */
व्योम tep_clear_flag(काष्ठा tep_handle *tep, क्रमागत tep_flag flag)
अणु
	अगर (tep)
		tep->flags &= ~flag;
पूर्ण

/**
 * tep_test_flag - check the state of event parser flag
 * @tep: a handle to the tep_handle
 * @flag: flag to be checked
 *
 * This वापसs the state of the requested tep flag.
 * Returns: true अगर the flag is set, false otherwise.
 */
bool tep_test_flag(काष्ठा tep_handle *tep, क्रमागत tep_flag flag)
अणु
	अगर (tep)
		वापस tep->flags & flag;
	वापस false;
पूर्ण

__hidden अचिन्हित लघु data2host2(काष्ठा tep_handle *tep, अचिन्हित लघु data)
अणु
	अचिन्हित लघु swap;

	अगर (!tep || tep->host_bigendian == tep->file_bigendian)
		वापस data;

	swap = ((data & 0xffULL) << 8) |
		((data & (0xffULL << 8)) >> 8);

	वापस swap;
पूर्ण

__hidden अचिन्हित पूर्णांक data2host4(काष्ठा tep_handle *tep, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक swap;

	अगर (!tep || tep->host_bigendian == tep->file_bigendian)
		वापस data;

	swap = ((data & 0xffULL) << 24) |
		((data & (0xffULL << 8)) << 8) |
		((data & (0xffULL << 16)) >> 8) |
		((data & (0xffULL << 24)) >> 24);

	वापस swap;
पूर्ण

__hidden  अचिन्हित दीर्घ दीर्घ
data2host8(काष्ठा tep_handle *tep, अचिन्हित दीर्घ दीर्घ data)
अणु
	अचिन्हित दीर्घ दीर्घ swap;

	अगर (!tep || tep->host_bigendian == tep->file_bigendian)
		वापस data;

	swap = ((data & 0xffULL) << 56) |
		((data & (0xffULL << 8)) << 40) |
		((data & (0xffULL << 16)) << 24) |
		((data & (0xffULL << 24)) << 8) |
		((data & (0xffULL << 32)) >> 8) |
		((data & (0xffULL << 40)) >> 24) |
		((data & (0xffULL << 48)) >> 40) |
		((data & (0xffULL << 56)) >> 56);

	वापस swap;
पूर्ण

/**
 * tep_get_header_page_size - get size of the header page
 * @tep: a handle to the tep_handle
 *
 * This वापसs size of the header page
 * If @tep is शून्य, 0 is वापसed.
 */
पूर्णांक tep_get_header_page_size(काष्ठा tep_handle *tep)
अणु
	अगर (tep)
		वापस tep->header_page_size_size;
	वापस 0;
पूर्ण

/**
 * tep_get_header_बारtamp_size - get size of the बारtamp in the header page
 * @tep: a handle to the tep_handle
 *
 * This वापसs size of the बारtamp in the header page
 * If @tep is शून्य, 0 is वापसed.
 */
पूर्णांक tep_get_header_बारtamp_size(काष्ठा tep_handle *tep)
अणु
	अगर (tep)
		वापस tep->header_page_ts_size;
	वापस 0;
पूर्ण

/**
 * tep_get_cpus - get the number of CPUs
 * @tep: a handle to the tep_handle
 *
 * This वापसs the number of CPUs
 * If @tep is शून्य, 0 is वापसed.
 */
पूर्णांक tep_get_cpus(काष्ठा tep_handle *tep)
अणु
	अगर (tep)
		वापस tep->cpus;
	वापस 0;
पूर्ण

/**
 * tep_set_cpus - set the number of CPUs
 * @tep: a handle to the tep_handle
 *
 * This sets the number of CPUs
 */
व्योम tep_set_cpus(काष्ठा tep_handle *tep, पूर्णांक cpus)
अणु
	अगर (tep)
		tep->cpus = cpus;
पूर्ण

/**
 * tep_get_दीर्घ_size - get the size of a दीर्घ पूर्णांकeger on the traced machine
 * @tep: a handle to the tep_handle
 *
 * This वापसs the size of a दीर्घ पूर्णांकeger on the traced machine
 * If @tep is शून्य, 0 is वापसed.
 */
पूर्णांक tep_get_दीर्घ_size(काष्ठा tep_handle *tep)
अणु
	अगर (tep)
		वापस tep->दीर्घ_size;
	वापस 0;
पूर्ण

/**
 * tep_set_दीर्घ_size - set the size of a दीर्घ पूर्णांकeger on the traced machine
 * @tep: a handle to the tep_handle
 * @size: size, in bytes, of a दीर्घ पूर्णांकeger
 *
 * This sets the size of a दीर्घ पूर्णांकeger on the traced machine
 */
व्योम tep_set_दीर्घ_size(काष्ठा tep_handle *tep, पूर्णांक दीर्घ_size)
अणु
	अगर (tep)
		tep->दीर्घ_size = दीर्घ_size;
पूर्ण

/**
 * tep_get_page_size - get the size of a memory page on the traced machine
 * @tep: a handle to the tep_handle
 *
 * This वापसs the size of a memory page on the traced machine
 * If @tep is शून्य, 0 is वापसed.
 */
पूर्णांक tep_get_page_size(काष्ठा tep_handle *tep)
अणु
	अगर (tep)
		वापस tep->page_size;
	वापस 0;
पूर्ण

/**
 * tep_set_page_size - set the size of a memory page on the traced machine
 * @tep: a handle to the tep_handle
 * @_page_size: size of a memory page, in bytes
 *
 * This sets the size of a memory page on the traced machine
 */
व्योम tep_set_page_size(काष्ठा tep_handle *tep, पूर्णांक _page_size)
अणु
	अगर (tep)
		tep->page_size = _page_size;
पूर्ण

/**
 * tep_is_file_bigendian - वापस the endian of the file
 * @tep: a handle to the tep_handle
 *
 * This वापसs true अगर the file is in big endian order
 * If @tep is शून्य, false is वापसed.
 */
bool tep_is_file_bigendian(काष्ठा tep_handle *tep)
अणु
	अगर (tep)
		वापस (tep->file_bigendian == TEP_BIG_ENDIAN);
	वापस false;
पूर्ण

/**
 * tep_set_file_bigendian - set अगर the file is in big endian order
 * @tep: a handle to the tep_handle
 * @endian: non zero, अगर the file is in big endian order
 *
 * This sets अगर the file is in big endian order
 */
व्योम tep_set_file_bigendian(काष्ठा tep_handle *tep, क्रमागत tep_endian endian)
अणु
	अगर (tep)
		tep->file_bigendian = endian;
पूर्ण

/**
 * tep_is_local_bigendian - वापस the endian of the saved local machine
 * @tep: a handle to the tep_handle
 *
 * This वापसs true अगर the saved local machine in @tep is big endian.
 * If @tep is शून्य, false is वापसed.
 */
bool tep_is_local_bigendian(काष्ठा tep_handle *tep)
अणु
	अगर (tep)
		वापस (tep->host_bigendian == TEP_BIG_ENDIAN);
	वापस 0;
पूर्ण

/**
 * tep_set_local_bigendian - set the stored local machine endian order
 * @tep: a handle to the tep_handle
 * @endian: non zero, अगर the local host has big endian order
 *
 * This sets the endian order क्रम the local machine.
 */
व्योम tep_set_local_bigendian(काष्ठा tep_handle *tep, क्रमागत tep_endian endian)
अणु
	अगर (tep)
		tep->host_bigendian = endian;
पूर्ण

/**
 * tep_is_old_क्रमmat - get अगर an old kernel is used
 * @tep: a handle to the tep_handle
 *
 * This वापसs true, अगर an old kernel is used to generate the tracing events or
 * false अगर a new kernel is used. Old kernels did not have header page info.
 * If @tep is शून्य, false is वापसed.
 */
bool tep_is_old_क्रमmat(काष्ठा tep_handle *tep)
अणु
	अगर (tep)
		वापस tep->old_क्रमmat;
	वापस false;
पूर्ण

/**
 * tep_set_test_filters - set a flag to test a filter string
 * @tep: a handle to the tep_handle
 * @test_filters: the new value of the test_filters flag
 *
 * This sets a flag to test a filter string. If this flag is set, when
 * tep_filter_add_filter_str() API as called,it will prपूर्णांक the filter string
 * instead of adding it.
 */
व्योम tep_set_test_filters(काष्ठा tep_handle *tep, पूर्णांक test_filters)
अणु
	अगर (tep)
		tep->test_filters = test_filters;
पूर्ण
