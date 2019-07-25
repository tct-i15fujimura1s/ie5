# Test Page

## Directories
<ul>
{% for page in site.pages %}
{%   if page.url.last == "/" %}
  <dd><a href="{{ page.url }}">{{ page.title }}</a></ul>
{%   endif %}
{% endfor %}
</ul>
