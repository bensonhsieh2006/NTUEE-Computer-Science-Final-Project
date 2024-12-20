# sdl_bgi.spec - tested on Fedora 39

%global debug_package %{nil} 

Summary:       SDL2-based "GRAPHICS.H" implementation
Name:          SDL_bgi
Version:       3.0.2
Release:       1
License:       ZLib
Group:         Libraries
Source:        %{name}-%{version}.tar.gz
URL:           http://sdl_bgi.sourceforge.net/
BuildRequires: SDL2-devel
Prefix:        %{_prefix}
BuildRoot:     %{_tmppath}/%{name}-%{version}-buildroot

%description
SDL bgi is a graphics library (GRAPHICS.H) for C, C++, WebAssembly,
and Python. It's based on SDL2 and it's portable on many platforms.
SDL_bgi is functionally compatible with the original BGI in Turbo C
2.01 and Borland C++ 1.0, and with another implementation, WinBGIm. In
addition, SDL_bgi provides extensions for ARGB colours, mouse support,
vector fonts, and multiple windows.

%prep
%setup -q -n %{name}-%{version}

%build
cd src
make

%install
rm -rf $RPM_BUILD_ROOT
cd src
mkdir -p $RPM_BUILD_ROOT/%{_libdir}
mkdir -p $RPM_BUILD_ROOT/%{_includedir}
mkdir -p $RPM_BUILD_ROOT/%{_includedir}/SDL2/
mkdir -p $RPM_BUILD_ROOT/%{_docdir}/%{name}/demo/assets/
mkdir -p $RPM_BUILD_ROOT/%{_docdir}/%{name}/demo/shells/
mkdir -p $RPM_BUILD_ROOT/%{_docdir}/%{name}/test/
mkdir -p $RPM_BUILD_ROOT/%{_mandir}/man3/
# mkdir -p $RPM_BUILD_ROOT/%{python_sitelib}/
/usr/bin/install -m 644 graphics.h    $RPM_BUILD_ROOT/%{_includedir}
/usr/bin/install -m 644 SDL_bgi.h     $RPM_BUILD_ROOT/%{_includedir}/SDL2/
/usr/bin/install -m 644 lib%{name}.so $RPM_BUILD_ROOT/%{_libdir}
# /usr/bin/install -m 644 sdl_bgi.py    $RPM_BUILD_ROOT/%{python_sitelib}
cd ..
/usr/bin/install -m 644 doc/graphics.3.gz  $RPM_BUILD_ROOT/%{_mandir}/man3/
/usr/bin/install -m 644 demo/*.* $RPM_BUILD_ROOT/%{_docdir}/%{name}/demo/
/usr/bin/install -m 644 demo/tccrun $RPM_BUILD_ROOT/%{_docdir}/%{name}/demo/
/usr/bin/install -m 644 demo/Makefile $RPM_BUILD_ROOT/%{_docdir}/%{name}/demo/
/usr/bin/install -m 644 test/* $RPM_BUILD_ROOT/%{_docdir}/%{name}/test/
/usr/bin/install -m 644 demo/assets/* $RPM_BUILD_ROOT/%{_docdir}/%{name}/demo/assets/
/usr/bin/install -m 644 demo/shells/* $RPM_BUILD_ROOT/%{_docdir}/%{name}/demo/shells/

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(644,root,root,755)
%doc AUTHORS BUGS ChangeLog INSTALL_Emscripten.md
%doc INSTALL_GNU-Linux.md INSTALL_Windows.md INSTALL_macOS.md
%doc INSTALL_Python.md LICENSE README.md sdl_bgi.spec TODO VERSION
%attr(644,root,root) %{_libdir}/lib%{name}.so
%attr(644,root,root) %{_includedir}/SDL2/SDL_bgi.h
%attr(644,root,root) %{_includedir}/graphics.h
%attr(644,root,root) %{_mandir}/man3/graphics.3.gz
# %attr(644,root,root) %{python_sitelib}/sdl_bgi.py
%attr(644,root,root) %{_docdir}/%{name}/demo/*
%attr(644,root,root) %{_docdir}/%{name}/test/*

%changelog
* Fri Aug 12 2022 Guido Gonzato <guido.gonzato at gmail.com>
Added Python support.

* Sat May 28 2022 Guido Gonzato <guido.gonzato at gmail.com>
Improved document section.

* Tue Jan 2 2018 Guido Gonzato <guido.gonzato at gmail.com>
Slightly improved portability.

* Sun Oct 22 2017 Guido Gonzato <guido.gonzato at gmail.com>
Slightly improved portability.

* Thu Nov 6 2014 Guido Gonzato <guido.gonzato at gmail.com>
This is a generic rpm, also buildable on Ubuntu
