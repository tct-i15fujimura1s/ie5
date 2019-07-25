---
theme: jekyll-theme-modernist
---

# Test Page

## Directories
<ul>
{% for page in site.pages %}
{%   if page.url =~ %r!^/\w*/! %}
  <li><a href="{{ page.url }}">{{ page.title }}</a></li>
{%   endif %}
{% endfor %}
</ul>
