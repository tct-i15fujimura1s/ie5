# Test Page

## Pages
<dl>
{% for page in site.pages %}
  <dt><date>{{ page.date | date_to_string: "ordinal", "JP" }}</date></dt>
  <dd><a href="{{ page.url }}">{{ page.title }}</a></dd>
{% endfor %}
</dl>
